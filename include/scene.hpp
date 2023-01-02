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
  OrthographicCamera cam = OrthographicCamera(1, 1);
  void render();
  GLFWwindow *window;
};
#endif
