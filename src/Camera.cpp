#include <Camera.h>

Camera::Camera(){
    Start();
}
Camera::~Camera(){
    Destroy();
}

void Camera::Start(){
    this->front = Vector3f(0.0f, 0.0f, -1.0f);
    this->up = Vector3f(0.0f, -1.0f, 0.0f);
    this-> right = this->front.cross(this->up);
    this->yaw = 0.0f;
    this->pitch = 0.0f;
    this->first_mouse = true;

    Vector3f p(0.0f, 0.0f, 10.0f);
    setPos(p);
    this->lastTime = SDL_GetTicks();
}
void Camera::Update(){
    this->lastTime = deltaTime();

    updateMovement(this->lastTime);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    updateRotation(mouseX, mouseY, first_mouse, this->lastTime);
}
void Camera::Destroy(){ }

Matrix Camera::getViewMatrix(){
    return Transformation::lookat(this->pos, (this->front + this-> pos).normalized(), this->up);
}

void Camera::updateMovement(float deltaTime){
    float velocity = speed * deltaTime;

    if(e.key.keysym.sym == SDLK_w){
        this->pos = this->pos + this->front * Transformation::scale(speed);
    }
    if(e.key.keysym.sym == SDLK_s){
        this->pos = this->pos - this->front * Transformation::scale(speed);
    }
    if(e.key.keysym.sym == SDLK_d){
        this->pos = this->pos + this->right * Transformation::scale(speed);
    }
    if(e.key.keysym.sym == SDLK_a){
        this->pos = this->pos - this->right * Transformation::scale(speed);
    }
}
void Camera::updateRotation(int &mouseX, int &mouseY, bool &firstMouse, float deltaTime){
    float sensitivity = 0.1f;
    static int lastX = 1080 / 2, lastY = 960 / 2;

    if(firstMouse){
        lastX = mouseX;
        lastY = mouseY;
        firstMouse = false;
    }

    float offsetX = mouseX - lastX;
    float offsetY = lastY - mouseY;

    offsetX *= sensitivity;
    offsetY *= sensitivity;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
}

void Camera::setPos(Vector3f &p){
    this->pos = p;
}

float Camera::deltaTime(){
    uint32_t currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - this->lastTime) / 1000.0f;
    lastTime = currentTime;

    return deltaTime;
}