#ifndef PLANE_H
#define PLANE_H

#include "VAO.h"
#include "VBO.h"
#include "Math.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Triangle.h"
#include "ShaderProgram.h"

class Plane
{
public:

    Vector3 point;
    Vector3 normal;
    VAO *vao = nullptr;
    VBO *vbo = nullptr;
    Vector4 color;

    Plane();
    Plane(const Vector3 &point, const Vector3 &normal);
    virtual ~Plane();

    bool IsBehind(const Vector3 &point);
    bool IsInFront(const Vector3 &point);

    static Plane *FromTriangle(const Triangle &t);

    void RefreshData();
    void Render(ShaderProgram *program);

};

#endif // PLANE_H
