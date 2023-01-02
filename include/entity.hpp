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
  Entity(entt::registry & r, float *vertices, unsigned int vertex_count, VAO & vao, VBO &vbo);
  
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

#endif
