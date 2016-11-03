#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "VAO.h"
#include "VBO.h"
#include "Math.h"
#include "Vector3.h"
#include "ShaderProgram.h"

class Plane;
class Triangle
{
public:

    Vector4 color;
    VBO *vbo = nullptr;
    VAO *vao = nullptr;
    Vector3 p1, p2, p3;

    Triangle();
    Triangle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);
    virtual ~Triangle();

    // Returns the number of intersections
    int GetIntersectionWithPlane(const Plane &plane,
                                 Vector3 *intersection1,
                                 Vector3 *intersection2) const;

    bool SplitWithPlane(Plane *plane,
                        Triangle **splitTri1,
                        Triangle **splitTri2,
                        Triangle **splitTri3);

    void RefreshData();
    void Draw(ShaderProgram *program);
};

#endif // TRIANGLE_H
