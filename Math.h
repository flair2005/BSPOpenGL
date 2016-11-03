#ifndef MATH_H
#define MATH_H

#include <cstdlib>
#include <cmath>

class Vector3;
class Vector4;
class Math
{
private:
    Math();

public:
    static float Rand();
    static float RandAbs();
    static Vector3 RandVector3();
    static Vector4 RandVector4();
    static Vector3 RandAbsVector3();
    static Vector4 RandAbsVector4();
};

#endif // MATH_H
