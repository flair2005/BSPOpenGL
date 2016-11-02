#ifndef PLANE_H
#define PLANE_H

#include "VAO.h"
#include "VBO.h"
#include "Vector3.h"
#include "Triangle.h"
#include "ShaderProgram.h"

class Plane
{
public:

    Vector3 point;
    Vector3 normal;

    Plane();
    Plane(const Vector3 &point, const Vector3 &normal);
    virtual ~Plane();

    static Plane *FromTriangle(const Triangle &t);

    void RefreshData();
    void Draw(ShaderProgram *program);

    Vector4 color;
    VBO *vbo = nullptr;
    VAO *vao = nullptr;
    Vector3 p1, p2, p3;
};

#endif // PLANE_H
