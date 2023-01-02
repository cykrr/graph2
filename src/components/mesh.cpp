#include "glad/glad.h"

#include "components/mesh.hpp"
#include "components/model.hpp"
#include "components/shader.hpp"

 void draw_component(MeshComponent & mesh, ModelComponent &m, ShaderComponent &s)
{
        if (mesh.m_show_wireframe)
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(s.shader);
        Program::setMat4_id(s.shader, "m", m.matrix);

        Program::setVec4_id(s.shader, "color", mesh.m_color);
        glBindVertexArray(mesh.m_vao);
        glDrawArrays(GL_TRIANGLES, 0, mesh.m_vert_count);
}
