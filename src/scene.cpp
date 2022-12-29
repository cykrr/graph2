#include "scene.hpp"
#include "glm/mat4x4.hpp"

#include "components/model.hpp"

#include "components/scale.hpp"
#include "components/rotation.hpp"
#include "components/translate.hpp"

#include "components/drawable.hpp"


Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::render()
{
  Color clear("#656565");
  glClearColor(clear.x, clear.y, clear.z, clear.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto rotation_view = m_registry.view<RotationComponent, ModelComponent>();
  auto scale_view = m_registry.view<ScaleComponent, ModelComponent>();
  auto translate_view = m_registry.view<TranslateComponent, ModelComponent>();
  auto draw_view = m_registry.view<DrawableComponent, ModelComponent>();

  // SRT

  scale_view.each(
      [](ScaleComponent & sc, ModelComponent & mc) {
        scale_model(mc, sc);
      });

  rotation_view.each(
      [](RotationComponent & rc, ModelComponent & mc) {
        rotate_model(mc, rc);
      });

  translate_view.each(
      [](TranslateComponent & tc, ModelComponent & mc) {
        translate_model(mc, tc);
      });

  draw_view.each([](struct DrawableComponent &drawable,
                    struct ModelComponent &model) {
                   draw_component(drawable, model);
                 });
}
