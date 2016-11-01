#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"

class Camera
{
public:
    Vector3 position = Vector3::Zero;
    Quaternion rotation = Quaternion::Identity;

    Camera();
    virtual ~Camera();

    void Update();

    Matrix4 GetProjection() const;
    Matrix4 GetView() const;
};

#endif // CAMERA_H
