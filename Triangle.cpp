#include "Triangle.h"

Triangle::Triangle()
{
    vbo = new VBO();
    vao = new VAO();
}

Triangle::Triangle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3) : Triangle()
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Triangle::~Triangle()
{
    delete vao;
    delete vbo;
}

void Triangle::Update()
{
    Vector3 data[3] = {p1, p2, p3};
    vbo->Fill(&data[0], sizeof(Vector3) * 3);
    vao->BindVBO(vbo, 0, 3);
}

void Triangle::Draw()
{
    vao->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao->UnBind();
}
