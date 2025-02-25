#ifndef CAMERA_H
#define CAMERA_H

#include <IManager.h>

#include <Math.h>
#include <Transformation.h>

#include <SDL2/SDL.h>
#include <cstdint>

static float speed = 300.0f;

class Camera : public IManager{
public:
    Camera();
    ~Camera();

    void Start() override;
    void Update() override;
    void Destroy() override;

    Matrix getViewMatrix();

    float deltaTime();

    void updateMovement(float deltaTime);
    void updateRotation(int &mouseX, int &mouseY, bool &firstMouse, float deltaTime);

private:
    void setPos(Vector3f &p);

    Vector3f pos;
    Vector3f front, right, up;
    float yaw, pitch;
    uint32_t lastTime;
    bool first_mouse;

    SDL_Event e;
};

#endif