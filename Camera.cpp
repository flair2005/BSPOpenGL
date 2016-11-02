#include "Camera.h"

#include <iostream>

Camera::Camera()
{
    position = Vector3(0.0f, 20.0f, 70.0f);
}

Camera::~Camera()
{

}

void Camera::Update()
{
    // rotation = Quaternion::AngleAxis(0.01f, Vector3::Up) * rotation;
    // rotation = rotation.Normalized();
}

void Camera::OnKeyPressedEvent(QKeyEvent *ev)
{
    float camSpeed = 4.0f;
    float camRotSpeed = 0.05f;
    if (ev->key() == Qt::Key_W)
    {
        position += GetForward() * camSpeed;
    }
    else if (ev->key() == Qt::Key_S)
    {
        position += -GetForward() * camSpeed;
    }

    if (ev->key() == Qt::Key_A)
    {
        rotation = Quaternion::AngleAxis(camRotSpeed, GetUp()) * GetRotation();
    }
    else if (ev->key() == Qt::Key_D)
    {
        rotation = Quaternion::AngleAxis(-camRotSpeed, GetUp()) * GetRotation();
    }

    if (ev->key() == Qt::Key_Q)
    {
        rotation = Quaternion::AngleAxis(camRotSpeed, GetRight()) * GetRotation();
    }
    else if (ev->key() == Qt::Key_E)
    {
        rotation = Quaternion::AngleAxis(-camRotSpeed, GetRight()) * GetRotation();
    }
}

Quaternion Camera::GetRotation()
{
    return rotation.Normalized();
}

Vector3 Camera::GetForward()
{
    return Vector3(Vector3::Forward * GetRotation().Inversed());
}

Vector3 Camera::GetRight()
{
    return Vector3(Vector3::Right * GetRotation().Inversed());
}

Vector3 Camera::GetUp()
{
    return Vector3(Vector3::Up * GetRotation().Inversed());
}

Matrix4 Camera::GetProjection() const
{
    return glm::perspective(1.6f, 1.0f, 0.5f, 10000.0f);
}

Matrix4 Camera::GetView() const
{
    Matrix4 view =
            Matrix4::TranslateMatrix(position) *
            Matrix4::RotateMatrix(rotation);
    return view.Inversed();
}
