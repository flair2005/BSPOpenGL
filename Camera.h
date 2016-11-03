#ifndef CAMERA_H
#define CAMERA_H

#include <QKeyEvent>

#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"

class Camera
{
public:
    Vector3 position = Vector3::Zero;
    Quaternion rotation = Quaternion::Identity;

    const float camSpeed = 4.0f;
    const float camRotSpeed = 0.05f;

    Camera();
    virtual ~Camera();

    void Update();

    Quaternion GetRotation();
    Vector3 GetForward();
    Vector3 GetRight();
    Vector3 GetUp();

    Matrix4 GetProjection() const;
    Matrix4 GetView() const;
};

#endif // CAMERA_H
