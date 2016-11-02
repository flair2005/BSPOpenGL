#include "Plane.h"

Plane::Plane()
{
    vao = new VAO();
    vbo = new VBO();
}

Plane::Plane(const Vector3 &point, const Vector3 &normal) : Plane()
{
    this->point = point;
    this->normal = normal.Normalized();
}

Plane::~Plane()
{

}

Plane *Plane::FromTriangle(const Triangle &t)
{
    Plane *p = new Plane();
    return p;
}

void Plane::RefreshData()
{
    Vector3 v1 = Vector3::Cross(normal, normal + Vector3(1,0,0)).Normalized();
    Vector3 v2 = Vector3::Cross(normal, v1).Normalized();
    v1 *= 99999.0f; v2 *= 99999.0f;
    Vector3 data[6] = {-v1-v2, -v1+v2, v1-v2,
                       v1-v2, -v1+v2, v1+v2};
    vbo->Fill(&data[0], sizeof(Vector3) * 6);
    vao->BindVBO(vbo, 0, 3);

}

void Plane::Draw(ShaderProgram *program)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    program->SetUniformVec4("color", Vector4(0,0,0,0.98));
    vao->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao->UnBind();
    glDisable(GL_BLEND);
}
