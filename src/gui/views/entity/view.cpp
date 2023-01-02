#include <entt/entity/registry.hpp>
#include "imgui.h"

#include "components/mesh.hpp"
#include "components/gui.hpp"

#include "components/scale.hpp"
#include "components/translate.hpp"
#include "components/rotation.hpp"

#include "gui/matrix.hpp"

void selected_entity_view_draw(entt::registry & r, entt::entity & selection) {
  ImGui::Begin("SelectedEntity");

  GUIComponent & nc = r.get<GUIComponent>(selection);
  static int selected_component = false;
  ImGui::Text("Components");
  ImGui::ListBox("##Components", &selected_component, [](void *data, int idx, const char ** out_text) {
                   Components::m_enum pos = ((Components::m_enum*)data)[idx];
                   *out_text = Components::m_name[pos];

                   return true;
                 }, &nc.components[0], nc.components.size());

  MeshComponent & dc = r.get<MeshComponent>(selection);
  ImGui::Text("Name: %s", nc.m_name);
  Components::m_enum component = nc.components[selected_component];

  switch (component) {
    case Components::MeshComponent:
      ImGui::Text("Type: %s", nc.m_type);
      ImGui::Text("Drawable Component");
      ImGui::Text("VAO id: %d", dc.m_vao);
      ImGui::Text("Vertex count: %d", dc.m_vert_count);
      if (ImGui::ColorEdit3("Color", &dc.m_color.r, ImGuiColorEditFlags_DisplayHex |
                            ImGuiColorEditFlags_InputRGB |
                            ImGuiColorEditFlags_NoAlpha)) {
      }
      ImGui::Checkbox("Wireframe", &dc.m_show_wireframe);
      break;
    case Components::ModelComponent:
      ImGui::Text("Model Matrix:");

      {
      ModelComponent & mc = r.get<ModelComponent>(selection);
      // yeah, about that..........
      matrix_draw(mc.matrix);
      }
      break;
    case Components::ShaderComponent:{
      ShaderComponent & s = r.get<ShaderComponent>(selection);
      ImGui::Text("Shader ID: %d", s.shader);
      break;
    }
    case Components::RotateComponent:{

      static RotationComponent  rc({glm::vec3(0.f), 0.f}); 
      ModelComponent & mc = r.get<ModelComponent>(selection);
      ImGui::Text("Rotation");
      static bool x=0, y=0, z=0;

      ImGui::Checkbox("X", (bool*)&x);
      ImGui::Checkbox("Y", (bool*)&y);
      ImGui::Checkbox("Z", (bool*)&z);

      rc.axis.x = x;
      rc.axis.y = y;
      rc.axis.z = z;

      bool needs_update = false;

      float degrees = rc.radians *180.f/3.14159;
      if (ImGui::SliderFloat("degrees", &degrees, 0.f, 360.f, "%f")) {
        needs_update = true;
      } else needs_update = false;
      if (needs_update)
        rotate_model(mc, rc);

      rc.radians= degrees*3.14159/180.f;}
      break;
    case Components::ScaleComponent:
      ScaleComponent & sc = r.get<ScaleComponent>(selection);
      ImGui::Text("Scale");
      ImGui::SliderFloat3("Axis", &sc.axis.x, 0, 2, "%.2f", 0);
      break;
  }

  ImGui::End();
}
