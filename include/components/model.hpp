#ifndef MODEL_COMP_H
#define MODEL_COMP_H
#include <glm/mat4x4.hpp>

// Model matrix: used for rotation, translation and scaling.

struct ModelComponent {
  glm::mat4 matrix;
  ModelComponent(const glm::mat4 & m) : matrix(m) {};
  ModelComponent(const ModelComponent &) = default;
};
#endif
