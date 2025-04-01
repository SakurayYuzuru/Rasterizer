#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <Math.h>
#include <Transformation.h>

#include <algorithm>

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
    Math::Vector3f position;
    Math::Vector3f front;
    Math::Vector3f up;
    Math::Vector3f right;
    Math::Vector3f worldup;

    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(Math::Vector3f _position = Math::Vector3f(0.0f, 0.0f, 20.0f), Math::Vector3f _up = Math::Vector3f(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH) : 
        front(Math::Vector3f(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
        this->position = _position;
        this->worldup = _up;
        this->yaw = _yaw;
        this->pitch = _pitch;

        updateCameraVectors();
    }
    Camera(float _posX, float _posY, float _posZ, float _upX, float _upY, float _upZ, float _yaw, float _pitch) : 
        front(Math::Vector3f(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
        this->position = Math::Vector3f(_posX, _posY, _posZ);
        this->worldup = Math::Vector3f(_upX, _upY, _upZ);
        this->yaw = _yaw;
        this->pitch = _pitch;

        updateCameraVectors();
    }

    Math::Matrix GetViewMatrix() const{
        return Transformation::lookat(this->position, this->position + this->front, this->worldup);
    }

    void ProcessKeyboard(Camera_Movement dir, float deltaTime){
        float velocity = this->movementSpeed * deltaTime;
        if(dir == FORWARD){
            this->position = this->position + this->front * velocity;
        }
        if(dir == BACKWARD){
            this->position = this->position - this->front * velocity;
        }
        if(dir == LEFT){
            this->position = this->position - this->right * velocity;
        }
        if(dir == RIGHT){
            this->position = this->position + this->right * velocity;
        }
    }
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true){
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if(constrainPitch){
            pitch = std::clamp(pitch, -89.0f, 89.0f);
        }

        updateCameraVectors();
    }
    void ProcessMouseScroll(float yoffset){
        this->zoom -= static_cast<float>(yoffset);
        this->zoom = std::clamp(this->zoom, 1.0f, 45.0f);
    }
private:
    void updateCameraVectors(){
        Math::Vector3f f(std::cos(Math::radians(this->yaw)) * std::cos(Math::radians(this->pitch)),
                        std::sin(Math::radians(this->pitch)),
                        std::sin(Math::radians(this->yaw)) * std::cos(Math::radians(this->pitch)));

        this->front = f.normalized();
        this->right = this->front.cross(this->worldup).normalized();
        this->up = this->right.cross(this->front).normalized();
    }
};

#endif