#include "components/drawable.hpp"
 void draw_component(DrawableComponent & d)
{
        // printf("shader: %d\n", d.m_shader.get_id());
        // printf("vao: %d\n", d.m_vao.get_id());
        // printf("vert: %d\n", d.m_vert_count);
        d.m_shader.use();
        d.m_shader.setMat4("m", glm::mat4(1.f));
        d.m_vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, d.m_vert_count);
}
