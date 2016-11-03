#include "Math.h"

#include "Vector3.h"
#include "Vector4.h"

Math::Math()
{
}

float Math::Rand()
{
    return ( rand() % 1000 - 500) / 500.0f;
}

float Math::RandAbs()
{
    return Rand() * 0.5f + 0.5f;
}

Vector3 Math::RandVector3()
{
    return Vector3(Rand(), Rand(), Rand());
}

Vector4 Math::RandVector4()
{
    return Vector4(Rand(), Rand(), Rand(), Rand());
}

Vector3 Math::RandAbsVector3()
{
    return Vector3(RandAbs(), RandAbs(), RandAbs());
}

Vector4 Math::RandAbsVector4()
{
    return Vector4(RandAbs(), RandAbs(), RandAbs(), RandAbs());
}
