#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <IManager.h>

#include <Math.h>
#include <Transformation.h>
#include <Global.h>

#include <SDL2/SDL.h>
#include <cstdint>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

static const float YAW         = -90.0f;
static const float PITCH       =  0.0f;
static const float SPEED       =  0.5f;
static const float SENSITIVITY =  0.1f;
static const float ZOOM        =  45.0f;

class Camera : public IManager{
public:
    Camera();
    ~Camera();

    Math::Matrix getViewMatrix();

    float deltaTime();

    void ProcessKeyboard(Camera_Movement dir);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);

private:
    void Start() override;
    void Update() override;
    void Destroy() override;

    void updateCameraVectors();

private:
    Math::Vector3f position;
    Math::Vector3f front;
    Math::Vector3f up;
    Math::Vector3f right;
    Math::Vector3f worldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    uint32_t lastTime;
};

#endif