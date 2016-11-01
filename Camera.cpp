#include "Camera.h"
#include <iostream>
Camera::Camera()
{
}

Camera::~Camera()
{

}

void Camera::Update()
{
    rotation = Quaternion::AngleAxis(0.01f, Vector3::Up) * rotation;
    rotation = rotation.Normalized();
    //position.x += 0.1f;
}

Matrix4 Camera::GetProjection() const
{
    return glm::perspective(1.6f, 1.0f, 0.5f, 100.0f);
}

Matrix4 Camera::GetView() const
{
    Matrix4 view =
            Matrix4::TranslateMatrix(position) *
            Matrix4::RotateMatrix(rotation);
    return view.Inversed();
}
