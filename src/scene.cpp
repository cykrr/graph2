#include "scene.hpp"
#include "glm/mat4x4.hpp"
#include "components/view_proj.hpp"


Scene::Scene() {
  entt::entity ent = m_registry.create();
}

entt::entity Scene::create_entity()
{
  return m_registry.create();
}

Scene::~Scene() {

}
