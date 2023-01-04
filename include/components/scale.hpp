#ifndef SCALE_COMP_H
#define SCALE_COMP_H
#include "components/model.hpp"
#include <glm/vec3.hpp>

struct ScaleComponent {
  ScaleComponent(const ScaleComponent &) = default;
  ScaleComponent(ScaleComponent &) = default;
  ScaleComponent(ScaleComponent &&) = default;
  ScaleComponent() {axis = glm::vec3(1.f);}
  ScaleComponent(float x, float y, float z = 0) {axis = glm::vec3(x,y,z);}
  glm::vec3 axis;
};

void scale_model(ModelComponent & mc, const ScaleComponent & rc);
#endif
