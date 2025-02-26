#include <Camera.h>

Camera::Camera(){
    Start();
}
Camera::~Camera(){
    Destroy();
}

void Camera::Start(){
    this->position = Vector3f(0.0f, 0.0f, 0.0f);
    this->up = Vector3f(0.0f, 1.0f, 0.0f);
    this->yaw = YAW;
    this->pitch = PITCH;
    this->front = Vector3f(0.0f, 0.0f, -1.0f);
    this->MovementSpeed = SPEED;
    this->MouseSensitivity = SENSITIVITY;
    this->Zoom = ZOOM;
}
void Camera::Update(){

}
void Camera::Destroy(){ }

Matrix Camera::getViewMatrix(){
    return Transformation::lookAt(this->position, this->position + this->front, this->up);
}

