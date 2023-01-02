#ifndef SCALE_COMP_H
#define SCALE_COMP_H
#include "model.hpp"
#include <glm/vec3.hpp>

struct ScaleComponent {
  glm::vec3 axis;
  ScaleComponent(const ScaleComponent &) = default;
  ScaleComponent(ScaleComponent &) = default;
  ScaleComponent(ScaleComponent &&) = default;
  ScaleComponent() {axis = glm::vec3(1.f);}
};

void scale_model(ModelComponent & mc, const ScaleComponent & rc);
#endif
