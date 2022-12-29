#ifndef SCENE_H
#define SCENE_H
#include "entt/entity/registry.hpp"
class Scene {
public:
  Scene();
  ~Scene();
  entt::entity create_entity();
  entt::registry m_registry;
  void render();
private:
  
};
#endif
