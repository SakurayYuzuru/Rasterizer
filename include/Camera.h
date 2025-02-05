#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <Math.h>

enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera{
public:
    Camera();
    Camera(Vector3f position, Vector3f up, float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    ~Camera();

    void ProcessMouseScroll(float yoffset);

private:
    void updateCameraVectors();

    Vector3f Position;
    Vector3f Front;
    Vector3f Up;
    Vector3f Right;
    Vector3f WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
};

#endif