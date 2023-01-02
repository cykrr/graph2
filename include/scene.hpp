#ifndef SCENE_H
#define SCENE_H
#include "entt/entity/registry.hpp"
#include "cam.hpp"
class Scene {
public:
  Scene();
  ~Scene();
  entt::entity create_entity();
  entt::registry m_registry;
  Camera cam = Camera();
  void render();
  GLFWwindow *window;
};
#endif
