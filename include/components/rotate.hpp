#ifndef ROTATION_COMP_H
#define ROTATION_COMP_H
#include "model.hpp"
#include <glm/vec3.hpp>

struct RotateComponent {
  glm::vec3 axis;
  float radians;
  RotateComponent(const RotateComponent &) = default;
};
void rotate_model(ModelComponent & mc, const RotateComponent & rc);
#endif
