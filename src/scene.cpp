#include "glm/mat4x4.hpp"

#include "components/model.hpp"

#include "components/scale.hpp"
#include "components/rotate.hpp"
#include "components/translate.hpp"

#include "components/mesh.hpp"

#include "scene.hpp"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::render()
{
  Color clear("#202020");
  glClearColor(clear.x, clear.y, clear.z, clear.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto draw_view = m_registry.view<MeshComponent, ModelComponent, ShaderComponent>();

  // SRT

  auto scale_view = m_registry.view<ScaleComponent, ModelComponent>();
  auto rotate_view = m_registry.view<RotateComponent, ModelComponent>();
  auto translate_view = m_registry.view<TranslateComponent, ModelComponent>();

  translate_view.each(
      [](TranslateComponent & tc, ModelComponent & mc) {
        translate_model(mc, tc);
      });

  scale_view.each(
      [](ScaleComponent & sc, ModelComponent & mc) {
        scale_model(mc, sc);
      });

  rotate_view.each(
      [](RotateComponent & rc, ModelComponent & mc) {
        rotate_model(mc, rc);
      });


  draw_view.each([](struct MeshComponent &drawable,
                    struct ModelComponent &model,
                    struct ShaderComponent &shader) {
                   draw_component(drawable, model, shader);
                 });
}
