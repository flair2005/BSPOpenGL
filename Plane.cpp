#include "Plane.h"

Plane::Plane()
{
    vao = new VAO();
    vbo = new VBO();
    color = Vector4(Math::Rand(), Math::Rand(), Math::Rand(), 0.5f);
}

Plane::Plane(const Vector3 &point, const Vector3 &normal) : Plane()
{
    this->point = point;
    this->normal = normal.Normalized();
    RefreshData();
}

Plane::~Plane()
{

}

bool Plane::IsBehind(const Vector3 &point)
{
    return Vector3::Dot(normal, point - this->point) <= 0.05;
}

bool Plane::IsInFront(const Vector3 &point)
{
    return Vector3::Dot(normal, point - this->point) >= -0.05;
}

Plane *Plane::FromTriangle(const Triangle &t)
{
    Plane *p = new Plane(t.p1, Vector3::Cross(t.p2-t.p1, t.p3-t.p1));
    p->color = t.color;
    return p;
}

void Plane::RefreshData()
{
    Vector3 v1 = Vector3::Cross(normal, normal + Vector3(1,0,0)).Normalized();
    Vector3 v2 = Vector3::Cross(normal, v1).Normalized();
    v1 *= 100.0f; v2 *= 100.0f;
    Vector3 data[6] = {point-v1-v2, point-v1+v2, point+v1-v2,
                       point+v1-v2, point-v1+v2, point+v1+v2};
    vbo->Fill(&data[0], sizeof(Vector3) * 6);
    vao->BindVBO(vbo, 0, 3);

}

void Plane::Render(ShaderProgram *program)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    program->SetUniformVec4("color", color);
    vao->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao->UnBind();
    glDisable(GL_BLEND);
}
