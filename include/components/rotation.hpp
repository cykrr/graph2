#ifndef ROTATION_COMP_H
#define ROTATION_COMP_H
#include <glm/vec3.hpp>

struct RotationComponent {
  glm::vec3 axis;
  float radians;
  RotationComponent(const RotationComponent &) = default;
};
#endif
