#ifndef SCALE_COMP_H
#define SCALE_COMP_H
#include "model.hpp"
#include <glm/vec3.hpp>

struct ScaleComponent {
  ScaleComponent(const ScaleComponent &) = default;
  glm::vec3 axis;
};

void scale_model(ModelComponent & mc, const ScaleComponent & rc);
#endif
