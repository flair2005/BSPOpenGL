#include "Triangle.h"

#include "Segment.h"
#include "GLWidget.h"

Triangle::Triangle()
{
    vbo = new VBO();
    vao = new VAO();
    color = Vector4(Math::RandAbsVector3(), 1);
    RefreshData();
}

Triangle::Triangle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3) : Triangle()
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    RefreshData();
}

Triangle::~Triangle()
{
    delete vao;
    delete vbo;
}

bool Triangle::IsWhollyInFrontOfPlane(Plane *plane)
{
    return Vector3::Dot((p1 - plane->point), plane->normal) > -0.05 &&
           Vector3::Dot((p2 - plane->point), plane->normal) > -0.05 &&
           Vector3::Dot((p3 - plane->point), plane->normal) > -0.05;
}

bool Triangle::IsWhollyBehindOfPlane(Plane *plane)
{
    return Vector3::Dot((p1 - plane->point), plane->normal) <= 0.005 &&
           Vector3::Dot((p2 - plane->point), plane->normal) <= 0.005 &&
           Vector3::Dot((p3 - plane->point), plane->normal) <= 0.005;
}

bool Triangle::IsPartOfPlane(Plane *plane) const
{
    Segment segments[3] = {Segment(p1,p2), Segment(p1,p3), Segment(p2,p3)};

    int numPartOfPlane = 0;
    for (const Segment &s : segments)
    {
        if (s.IsPartOfPlane(plane))
        {
            ++numPartOfPlane;
            if (numPartOfPlane >= 2) { return true; }
        }
    }
    return false;
}

int Triangle::GetIntersectionWithPlane(const Plane &plane,
                                       Vector3 *intersection1,
                                       Vector3 *intersection2) const
{
    Segment segments[3] = { Segment(p1,p2), Segment(p1,p3), Segment(p2,p3) };

    int numIntersections = 0; // 0, 1 or 2 (¿1?)
    Vector3 intersectionResult;
    for (const Segment &s : segments)
    {
        if (s.GetIntersection(plane, &intersectionResult))
        {
            ++numIntersections;
            if (numIntersections == 1) { *intersection1 = intersectionResult; }
            else
            {
                if (*intersection1 != intersectionResult)
                {
                    *intersection2 = intersectionResult;
                    break;
                }
            }
        }
    }
    return numIntersections;
}

bool Triangle::SplitWithPlane(Plane *plane,
                              Triangle **splitTri1,
                              Triangle **splitTri2,
                              Triangle **splitTri3)
{
    Segment s12(p1,p2), s13(p1,p3), s23(p2,p3);

    Vector3 intersection1, intersection2;
    int numIntersections = GetIntersectionWithPlane(*plane, &intersection1, &intersection2);
    if ( numIntersections > 1 )
    {
        Segment intersectionSegment(intersection1, intersection2);

        Vector3 pointToSideAAlone,              // One point will be alone in one side of the plane alone
                pointToSideB_1, pointToSideB_2; // Two points are on one side of the plane
        int o1 = intersectionSegment.GetOrientation(p1);
        int o2 = intersectionSegment.GetOrientation(p2);
        int o3 = intersectionSegment.GetOrientation(p3);
        if (o1 == o2)
        {
            pointToSideAAlone = p3;
            pointToSideB_1 = p1;
            pointToSideB_2 = p2;
        }
        else if (o1 == o3)
        {
            pointToSideAAlone = p2;
            pointToSideB_1 = p1;
            pointToSideB_2 = p3;
        }
        else
        {
            pointToSideAAlone = p1;
            pointToSideB_1 = p2;
            pointToSideB_2 = p3;
        }

        *splitTri1 = new Triangle(intersection1, intersection2, pointToSideAAlone);
        *splitTri2 = new Triangle(intersection1, intersection2, pointToSideB_1);

        // Decide whether to connect intersection1 to B_1 or B_2 (one of them is incorrect)
        // Just treating the case...dont know if there's a better way to do this
        if (std::abs(Vector3::Dot((pointToSideB_1 - intersection1).Normalized(),
                                  (pointToSideB_1 - pointToSideAAlone).Normalized())) <= 0.001f)
        {
            *splitTri3 = new Triangle(intersection1, pointToSideB_1, pointToSideB_2);
        }
        else
        {
            *splitTri3 = new Triangle(intersection2, pointToSideB_1, pointToSideB_2);
        }

        (*splitTri1)->color = color;
        (*splitTri2)->color = color;
        (*splitTri3)->color = color;
        (*splitTri1)->RefreshData();
        (*splitTri2)->RefreshData();
        (*splitTri3)->RefreshData();

        return true;
    }
    return false;
}

void Triangle::RefreshData()
{
    Vector3 data[4] = {p1, p2, p3, p1};
    vbo->Fill(&data[0], sizeof(Vector3) * 4);
    vao->BindVBO(vbo, 0, 3);
}

void Triangle::Render(ShaderProgram *program)
{
    vao->Bind();

    program->SetUniformVec4("color", color);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    if (GLWidget::GetInstance()->seeTriDivisions)
    {
        program->SetUniformVec4("color", Vector4(Vector3::One - color.xyz(), 1));
        glLineWidth(1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, 4);
    }

    vao->UnBind();
}
