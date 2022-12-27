#include "glad/glad.h"
#include "components/drawable.hpp"
 void draw_component(DrawableComponent & d)
{
        if (d.m_show_wireframe)
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(d.m_shader);
        Program::setMat4_id(d.m_shader, "m", glm::mat4(1.f));
        Program::setVec4_id(d.m_shader, "color", d.m_color);
        glBindVertexArray(d.m_vao);
        glDrawArrays(GL_TRIANGLES, 0, d.m_vert_count);
}
