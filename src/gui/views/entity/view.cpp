#include <entt/entity/registry.hpp>
#include "imgui.h"
#include "components/drawable.hpp"
#include "components/gui.hpp"
#include "components/scale.hpp"
#include "components/translate.hpp"
//mv 
#include "components/rotation.hpp"
void selected_entity_view_draw(entt::registry & r, entt::entity & selection) {
  ImGui::Begin("SelectedEntity");

  GUIComponent & nc = r.get<GUIComponent>(selection);
  static int selected_component = false;
  ImGui::ListBox("Components", &selected_component, [](void *data, int idx, const char ** out_text) {
                   Components::m_enum pos = ((Components::m_enum*)data)[idx];
                   *out_text = Components::m_name[pos];

                   return true;
                 }, &nc.components[0], nc.components.size());

  DrawableComponent & dc = r.get<DrawableComponent>(selection);
  ImGui::Text("Name: %s", nc.m_name);
  ImGui::Text("Type: %s", nc.m_type);
  Components::m_enum component = nc.components[selected_component];

  switch (component) {
    case Components::DrawableComponent:
      ImGui::Text("Drawable Component");
      ImGui::Text("VAO id: %d", dc.m_vao);
      ImGui::Text("Shader id: %d", dc.m_shader);
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
      ImGui::Text(
          "%.2f %.2f %.2f %.2f\n%.2f %.2f %.2f %.2f\n"
          "%.2f %.2f %.2f %.2f\n%.2f %.2f %.2f %.2f\n",
          mc.matrix[0][0], mc.matrix[0][1], mc.matrix[0][2], mc.matrix[0][3],
          mc.matrix[1][0], mc.matrix[1][1], mc.matrix[1][2], mc.matrix[1][3],
          mc.matrix[2][0], mc.matrix[2][1], mc.matrix[2][2], mc.matrix[2][3],
          mc.matrix[3][0], mc.matrix[3][1], mc.matrix[3][2], mc.matrix[3][3]
        );
      }
      break;
    case Components::RotateComponent:{

    RotationComponent & rc = r.get<RotationComponent>(selection);
    ImGui::Text("Rotation");
    bool x = (bool)rc.axis.x, y = (bool)rc.axis.y, z = (bool)(rc.axis.z);

    ImGui::Checkbox("X", (bool*)&x);
    ImGui::Checkbox("Y", (bool*)&y);
    ImGui::Checkbox("Z", (bool*)&z);

    rc.axis.x = x;
    rc.axis.y = y;
    rc.axis.z = z;

    float degrees = rc.radians *180.f/3.14159;
    ImGui::SliderFloat("degrees", &degrees, 0.f, 360.f, "%f");
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
