#include "BSPNode.h"

#include "GLWidget.h"

BSPNode::BSPNode(Triangle *initialTriangle)
{
    splitPlane = Plane::FromTriangle(*initialTriangle);
    splitPlane->RefreshData();

    triangles.push_back(initialTriangle);
}

BSPNode::~BSPNode()
{
    delete splitPlane;
    for (Triangle *tri : triangles)
    {
        delete tri;
    }
    if (bspBehind) delete bspBehind;
    if (bspFront) delete bspFront;
}

void BSPNode::InsertTriangle(Triangle *tri)
{
    if (tri->IsPartOfPlane(splitPlane))
    {
        triangles.push_back(tri);
    }
    else
    {
        if (tri->IsWhollyInFrontOfPlane(splitPlane))
        {
            if (bspFront)
            {
                bspFront->InsertTriangle(tri);
            }
            else
            {
                bspFront = new BSPNode(tri);
            }
        }
        else if (tri->IsWhollyBehindOfPlane(splitPlane))
        {
            if (bspBehind)
            {
                bspBehind->InsertTriangle(tri);
            }
            else
            {
                bspBehind = new BSPNode(tri);
            }
        }
        else
        {
            // Triangle is intersecting !!!
            Vector3 int1, int2;
            if (tri->GetIntersectionWithPlane(*splitPlane, &int1, &int2) > 0) // This should always throw > 0
            {
                // Split the triangle into 2 parts (one of them must be triangulated, so 3 triangles)
                Triangle *splitTri1, *splitTri2, *splitTri3;
                tri->SplitWithPlane(splitPlane, &splitTri1, &splitTri2, &splitTri3);
                InsertTriangle(splitTri1);
                InsertTriangle(splitTri2);
                InsertTriangle(splitTri3);
            }
            else
            {
                std::cerr << "This should never happen dafuq..." << std::endl;
            }
        }
    }
}

void BSPNode::Render(const Vector3 &viewPoint,
                     ShaderProgram *program) const
{
    BSPNode *firstToRender  = nullptr;
    BSPNode *secondToRender = nullptr;

    if (splitPlane->IsBehind(viewPoint))
    {
        firstToRender = bspFront;
        secondToRender = bspBehind;
    }
    else
    {
        firstToRender = bspBehind;
        secondToRender = bspFront;
    }

    if (firstToRender) firstToRender->Render(viewPoint, program);
    for (Triangle *tri : triangles)
    {
        tri->Render(program);
    }
    if (secondToRender) secondToRender->Render(viewPoint, program);

    if (GLWidget::GetInstance()->seePlanes)
    {
        splitPlane->Render(program);
    }
}
