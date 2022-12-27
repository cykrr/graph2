#include "glad/glad.h"
#include "components/drawable.hpp"
 void draw_component(DrawableComponent & d)
{
        // printf("shader: %d\n", d.m_shader.get_id());
        // printf("vao: %d\n", d.m_vao.get_id());
        // printf("vert: %d\n", d.m_vert_count);
        glUseProgram(d.m_shader);
        Program::setMat4_id(d.m_shader, "m", glm::mat4(1.f));
        Program::setVec4_id(d.m_shader, "color", d.m_color);
        glBindVertexArray(d.m_vao);
        glDrawArrays(GL_TRIANGLES, 0, d.m_vert_count);
}
