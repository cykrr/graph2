
#include "components/mesh.hpp"
#include "components/rotate.hpp"
#include "components/scale.hpp"
#include "components/model.hpp"
#include "components/translate.hpp"

#include "VAO.hpp"
#include "VBO.hpp"
#include "shaders.hpp"

#include "entity.hpp"

#include <entt/entity/registry.hpp>


Entity::Entity(entt::registry & r, const float *vertices, const unsigned int *indices, unsigned int vertex_count, unsigned int indices_count, VAO & vao, VBO &vbo, VBO & ebo) : Entity(r) 
{
  vao.bind();
  vbo.bind_buffer();
  vbo.bind_buffer();
}


Entity::Entity(entt::registry & r, const float *vertices, unsigned int vertex_count,
               VAO &vao, VBO &vbo) : Entity(r)
{

  vao.bind();
  vbo.bind_buffer();
  vbo.send_data(3*vertex_count*sizeof(float), (float*)vertices, GL_STATIC_DRAW);
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

void add_position(Entity & e, float x, float y, float z)
{
  e.emplace<TranslateComponent>(TranslateComponent{glm::vec3(x, y, z)});
}

void set_position(Entity & e, float x, float y, float z)
{
  e.get<TranslateComponent>().position = glm::vec3(x, y, z);
}


void add_scale(Entity & e, float x, float y, float z)
{

  e.emplace<ScaleComponent>(ScaleComponent(x,y,z));
}
