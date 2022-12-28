#ifndef TRANSLATE_COMP_H
#define TRANSLATE_COMP_H
#include <glm/vec3.hpp>

struct TranslateComponent {
  TranslateComponent(const TranslateComponent &) = default;
  glm::vec3 position;
};
#endif
