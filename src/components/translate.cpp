#include <cstdio>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "components/translate.hpp"
#include "components/model.hpp"

void translate_model(ModelComponent & mc, const TranslateComponent & tc) {
  // mc.matrix = glm::translate(glm::mat4(1.f), tc.position);
  mc.matrix = glm::translate(mc.matrix, tc.position);
}
