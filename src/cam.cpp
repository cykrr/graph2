#include "cam.hpp"
OrthographicCamera::OrthographicCamera(int width, int height)
{
    update(width, height);
}


void OrthographicCamera::update(int width, int height)
{
    std::cout << "Update matrix ortho\n";
    this->matrix = glm::ortho(0.f, static_cast<float>(width), 
            0.f, static_cast<float>(height), -1.0f, 1.0f);
}

glm::vec3 PerspectiveCamera::vUp = glm::vec3(0.f, 1.f, 0.f);
glm::vec3 PerspectiveCamera::vFront = glm::vec3(0.f, 0.f, -1.f);

PerspectiveCamera::PerspectiveCamera() : Camera() {
    pos = glm::vec3(0.f, 0.f, -3.f);
}

PerspectiveCamera::PerspectiveCamera(int w, int h) : PerspectiveCamera() {
    speed = 2.5f;
    mV = glm::mat4(1.0f);
    mM = mV;
    mP = glm::perspective(glm::radians(45.0f), (float)w/(float)h, 0.1f, 100.f);
    update(w,h);
}

void PerspectiveCamera::update(int w, int h) {
    mV = glm::lookAt(pos, pos + vFront, vUp);
    mP = glm::perspective(glm::radians(45.0f), (float)w/(float)h, 0.0f, 100.f);
    matrix = mP * mV * mM;
}

void PerspectiveCamera::moveFront(){
    pos += speed * vFront * dt;
}

void PerspectiveCamera::moveBack(){
    pos -= speed * vFront * dt;
}

void PerspectiveCamera::moveLeft(){
    pos -= glm::normalize(glm::cross(vFront, vUp)) * speed * dt;
}

void PerspectiveCamera::moveRight(){
    pos += glm::normalize(glm::cross(vFront, vUp)) * speed * dt;
}

void PerspectiveCamera::moveUp(){}
void PerspectiveCamera::moveDown(){}

const glm::vec3 Cam3D::up = glm::vec3(0.f, 1.f, 0.f);

Cam3D::Cam3D() {
   pos = glm::vec3(0.f, 0.f, 3.f);
   front = glm::vec3(0.f, 0.f, -1.f);
}


void Cam3D::moveFront() {
    this->pos += this->front * this->speed * dt ;
}

void Cam3D::update(int w, int h) {
    this->projection = glm::perspective(glm::radians(45.f),
            (float)w / (float)h, ZNEAR, ZFAR);
}

void Cam3D::updateDirection() {
    if(this->pitch > 89.0f) 
        this->pitch = 89.f;
    if(this->pitch < -89.f)
        this->pitch = -89.f;


    this->direction.x = cos(glm::radians(this->yaw));
    this->direction.x *= cos(glm::radians(this->pitch));

    this->direction.y = sin(glm::radians(this->pitch));

    this->direction.z = sin(glm::radians(this->yaw));
    this->direction.z *= cos(glm::radians(this->pitch));

    
    this->front = glm::normalize(this->direction);


}
