#ifndef TRANSLATE_COMP_H
#define TRANSLATE_COMP_H
#include <glm/vec3.hpp>
#include "components/model.hpp"

struct TranslateComponent {
  TranslateComponent(const TranslateComponent &) = default;
  glm::vec3 position;
};
void translate_model(ModelComponent & mc, const TranslateComponent & rc);
#endif
