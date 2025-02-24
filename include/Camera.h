#ifndef CAMERA_H
#define CAMERA_H

#include <IManager.h>

#include <Math.h>
#include <Transformation.h>

#include <SDL2/SDL.h>

static float speed = 2.5f;

class Camera : public IManager{
public:
    Camera();
    ~Camera();

    void Start() override;
    void Update() override;
    void Destroy() override;

    Matrix getViewMatrix();

    void updateMovement(float deltaTime);
    void updateRotation(int &mouseX, int &mouseY, bool &firstMouse, float deltaTime);

private:
    void setPos(Vector3f &p);

    Vector3f pos;
    Vector3f front, right, up;
    float yaw, pitch;
    float lastTime;
    bool first_mouse;

    SDL_Event e;
};

#endif