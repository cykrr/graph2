#ifndef ROTATION_COMP_H
#define ROTATION_COMP_H
#include "model.hpp"
#include <glm/vec3.hpp>

struct RotationComponent {
  glm::vec3 axis;
  float radians;
  RotationComponent(const RotationComponent &) = default;
};
void rotate_model(ModelComponent & mc, const RotationComponent & rc);
#endif
