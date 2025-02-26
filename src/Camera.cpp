#include <Camera.h>

Camera::Camera(){
    Start();
}
Camera::~Camera(){
    Destroy();
}

void Camera::Start(){
    this->position = Vector3f(0.0f, 0.0f, -5.0f);
    this->up = Vector3f(0.0f, 1.0f, 0.0f);
    this->Yaw = YAW;
    this->Pitch = PITCH;
    this->front = Vector3f(0.0f, 0.0f, -1.0f);
    this->MovementSpeed = SPEED;
    this->MouseSensitivity = SENSITIVITY;
    this->Zoom = ZOOM;
    this->lastTime = SDL_GetTicks();
}
void Camera::Update(){

}
void Camera::Destroy(){ }

Matrix Camera::getViewMatrix(){
    return Transformation::lookat(this->position, this->position + this->front, this->up);
}

float Camera::deltaTime(){
    uint32_t curTime = SDL_GetTicks();
    float delta = static_cast<float>(curTime - this->lastTime) / 1000.0f;
    this->lastTime = curTime;

    return delta;
}

void Camera::ProcessKeyboard(Camera_Movement dir){
    float delta_time = deltaTime();
    float velocity = MovementSpeed * delta_time;
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

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch){
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    this->Yaw += xoffset;
    this->Pitch += yoffset;

    if(constrainPitch){
        if(this->Pitch > 89.0f){
            this->Pitch = 89.0f;
        }
        if(this->Pitch < -89.0f){
            this->Pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset){
    this->Zoom -= static_cast<float>(yoffset);
    if(this->Zoom < 1.0f){
        this->Zoom = 1.0f;
    }
    if(this->Zoom > 45.0f){
        this->Zoom = 45.0f;
    }
}

void Camera::updateCameraVectors(){
    Vector3f _front(std::cos(radians(Yaw) * std::cos(radians(Pitch))),
                    std::sin(radians(Pitch)),
                    std::sin(radians(Yaw) * std::cos(Pitch)));
    
    this->front = _front.normalized();
    this->right = this->front.cross(this->worldUp).normalized();
    this->up    = this->right.cross(this->front).normalized();
}