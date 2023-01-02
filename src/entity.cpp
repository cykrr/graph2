#include <entt/entity/registry.hpp>

#include "components/mesh.hpp"
#include "components/rotate.hpp"
#include "components/scale.hpp"
#include "components/model.hpp"

#include "VAO.hpp"
#include "VBO.hpp"
#include "shaders.hpp"

#include "entity.hpp"


Entity::Entity(entt::registry & r, float *vertices, unsigned int vertex_count, VAO &vao, VBO &vbo) : 
  Entity(r) {

  vao.bind();
  vbo.bind_buffer();
  vbo.send_data(3*vertex_count*sizeof(float), vertices, GL_STATIC_DRAW);
  vao.set_vertex_attr_ptr(0,  3, GL_FLOAT, 3 * sizeof(float), NULL);
  vao.enable_vertex_attr_array(0);

  vbo.unbind();
  vao.unbind();

  MeshComponent drawable = {
    vao.get_id(),
    vertex_count,
    false,
    Color("#ffffff"),
  };

  ModelComponent m = {
    glm::mat4(1.f)
  };

  ShaderComponent s = {
    Shaders::get_shader("main")
  };
  r.emplace<MeshComponent>(ent, drawable);
  r.emplace<ModelComponent>(ent, m);
  r.emplace<ShaderComponent>(ent, s);
}
