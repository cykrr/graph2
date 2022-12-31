#include "components/drawable.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"
#include "components/model.hpp"
#include "entt/entity/registry.hpp"
#include "VAO.hpp"
#include "VBO.hpp"


entt::entity create_entity(entt::registry & r, float *vertices, unsigned int vertex_count, VAO &vao, VBO &vbo) {

  vao.bind();
  vbo.bind_buffer();
  vbo.send_data(3*vertex_count*sizeof(float), vertices, GL_STATIC_DRAW);
  vao.set_vertex_attr_ptr(0,  3, GL_FLOAT, 3 * sizeof(float), NULL);
  vao.enable_vertex_attr_array(0);

  vbo.unbind();
  vao.unbind();

  DrawableComponent drawable = {
    Shaders::get_shader("main"),
    vao.get_id(),
    vertex_count,
    Color("#ffffff"),
    false,
  };

  ModelComponent m = {
    glm::mat4(1.f)
  };


  entt::entity e =r.create();
  r.emplace<DrawableComponent>(e, drawable);
  r.emplace<ModelComponent>(e, m);
  return e;

}
