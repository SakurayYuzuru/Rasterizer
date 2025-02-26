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
static const float SPEED       =  2.5f;
static const float SENSITIVITY =  0.1f;
static const float ZOOM        =  45.0f;

class Camera : public IManager{
public:
    Camera();
    ~Camera();

    void Start() override;
    void Update() override;
    void Destroy() override;

    Matrix getViewMatrix();

    float deltaTime();
    void handleEvent(SDL_Event &_e);

private:
    Vector3f position;
    Vector3f front;
    Vector3f up;
    Vector3f right;
    Vector3f worldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
};

#endif