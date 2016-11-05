#include "Camera.h"

#include <iostream>
#include "Input.h"

Camera::Camera()
{
    position = Vector3(0.0f, 0.0f, 100.0f);
}

Camera::~Camera()
{

}

void Camera::Update()
{
    if (!Input::GetKey(Input::Key::Shift))
    {
        if (Input::GetKey(Input::Key::W))
        {
            rotation = Quaternion::AngleAxis(camRotSpeed, GetRight()) * GetRotation();
        }
        else if (Input::GetKey(Input::Key::S))
        {
            rotation = Quaternion::AngleAxis(-camRotSpeed, GetRight()) * GetRotation();
        }

        if (Input::GetKey(Input::Key::A))
        {
            rotation = Quaternion::AngleAxis(camRotSpeed, GetUp()) * GetRotation();
        }
        else if (Input::GetKey(Input::Key::D))
        {
            rotation = Quaternion::AngleAxis(-camRotSpeed, GetUp()) * GetRotation();
        }

    }
    else // Panning
    {
        if (Input::GetKey(Input::Key::W))
        {
            position += GetUp() * camSpeed;
        }
        else if (Input::GetKey(Input::Key::S))
        {
            position += -GetUp() * camSpeed;
        }

        if (Input::GetKey(Input::Key::A))
        {
            position += -GetRight() * camSpeed;
        }
        else if (Input::GetKey(Input::Key::D))
        {
            position += GetRight() * camSpeed;
        }
    }

    position += GetForward() * Input::GetMouseWheel() * 3.0f;
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
