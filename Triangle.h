#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector3.h"
#include "VAO.h"
#include "VBO.h"

class Triangle
{
public:

    VBO *vbo = nullptr;
    VAO *vao = nullptr;
    Vector3 p1, p2, p3;

    Triangle();
    Triangle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);
    virtual ~Triangle();

    void Update();
    void Draw();
};

#endif // TRIANGLE_H
