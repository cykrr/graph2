#include "gui/drawable.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "shaders.hpp"
void
Drawable::rotate(glm::vec3 & axis, float radians)
{
  this->model = glm::rotate(this->model, radians, axis);
}

void
Drawable::translate(const glm::vec3 & offset)
{
  this->model = glm::translate(this->model, offset);
}

void
Drawable::scale(glm::vec3 & axis)
{
  this->model = glm::scale(glm::mat4(1.f), axis);
}

void
Drawable::reset()
{
  this->model = glm::mat4(1.f);
}

Drawable::Drawable(const std::string  & shader_name)
{
  this->shader = Shaders::get_shader("main");
}


