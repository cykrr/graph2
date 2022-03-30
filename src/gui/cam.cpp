#include "gui/cam.hpp"
OrthographicCamera::OrthographicCamera(int width, int height)
{
    update(width, height);
}

void OrthographicCamera::update(int width, int height)
{
    std::cout << "Update matrix ortho\n";
    this->matrix = glm::ortho(0.f, static_cast<float>(width), 
            0.f, static_cast<float>(height), 0.1f, 100.0f);



}
