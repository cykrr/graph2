#ifndef GUI_MATRIX_H
#define GUI_MATRIX_H
#include "imgui.h"
#include <glm/mat4x4.hpp>

inline void matrix_draw(glm::mat4 & mat) {
      ImGui::Text(
          "%.2f %.2f %.2f %.2f\n%.2f %.2f %.2f %.2f\n"
          "%.2f %.2f %.2f %.2f\n%.2f %.2f %.2f %.2f\n",
          mat[0][0], mat[0][1], mat[0][2], mat[0][3],
          mat[1][0], mat[1][1], mat[1][2], mat[1][3],
          mat[2][0], mat[2][1], mat[2][2], mat[2][3],
          mat[3][0], mat[3][1], mat[3][2], mat[3][3]
        );
}
#endif

