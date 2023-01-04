#ifndef ENTITY_H
#define ENTITY_H
#include "VAO.hpp"
#include "VBO.hpp"
#include "entt/entity/registry.hpp"
struct Entity {
  Entity &operator=(const Entity &e) {
    this->ent = e.ent;
    return *this;
  }
  entt::registry &reg;
  entt::entity ent;
  Entity(entt::registry & r) : reg(r) {
      this->ent = r.create();
  }
  Entity(entt::registry & r, const float *vertices, unsigned int vertex_count, VAO & vao, VBO &vbo);

  Entity(entt::registry & r, const float *vertices, const unsigned int *indices, unsigned int vertex_count, unsigned int indices_count, VAO & vao, VBO &vbo, VBO & ebo);
  
  template <typename T>
  void emplace(T && component) {
    reg.emplace<T>(ent, component);
  }

  template <typename T>
  void emplace(T & component) {
    reg.emplace<T>(ent, component);
  }

  template <typename T, typename... Args>
  T& get() {
    return reg.get<T>(ent);
  }

};

void add_position(Entity & e, float x, float y, float z = 0);
void set_position(Entity & e, float x, float y, float z = 0);

void add_scale(Entity & e, float x, float y, float z = 0);

#endif
