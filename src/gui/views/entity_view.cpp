#include <entt/entity/registry.hpp>

#include "components/name.hpp"

#include "components/drawable.hpp"
#include "components/rotation.hpp"

#include "entities/cube.hpp"
#include "entities/triangle.hpp"

#include "gui.hpp"

void selected_entity_view_draw(entt::registry & r, entt::entity & selection);

void GUI::entity_view_draw(entt::registry &r)
{
  ImGui::Begin("Entities");
  ImGui::Text("Create entity:");
  // grab primitive and it's name
  std::tuple<const char *, entity_fn_t> entity_desc =  entity_type_picker_draw(r);

  // draw color
  static Color color("#202020");
  ImGui::ColorEdit3("Color", &color.r, 
                        ImGuiColorEditFlags_DisplayHex |
                        ImGuiColorEditFlags_InputRGB |
                        ImGuiColorEditFlags_NoAlpha
                        );

  static char buf[50] = "";
  if (
    ImGui::InputText("name", buf, 50,ImGuiInputTextFlags_EnterReturnsTrue) &&
    strlen(buf) != 0 
  ) {
    // get primitive type
    const char * n = std::get<0>(entity_desc);

    // get selected fn and call it to get the ent
    entt::entity e = std::get<1>(entity_desc)(r); 

    // Fill it's components
    NameComponent nc(buf,  n);
    m_scene.m_registry.emplace<NameComponent>(e, nc);

    DrawableComponent & c = r.get<DrawableComponent>(e);
    c.m_color = color;
  }

  static entt::entity selection;
  static bool selected = false;
  if (ImGui::BeginListBox("Entities")) {
    auto view = r.view<NameComponent>();
    view.each([](const entt::entity & ent, NameComponent &name) {
                 if (ImGui::Selectable(name.m_name, ent == selection)) {
                   selected = true;
                   selection = ent;
                 }
               });
    ImGui::EndListBox();
  }
  ImGui::End();
  if (selected) {
    selected_entity_view_draw(r,selection);
  }
}


  std::tuple<const char *, entity_fn_t> GUI::entity_type_picker_draw(entt::registry & r)
  {
    static const char * items_str[] = {"Triangle", "Cube"};

    const entity_fn_t items_func[10] = {create_triangle, create_cube};
    static entity_fn_t current_func = NULL;

    static int item_current = 0;

    ImGui::Combo("Type", &item_current, items_str, IM_ARRAYSIZE(items_str));
    current_func = items_func[item_current];
    return std::tuple<const char *, entity_fn_t>(items_str[item_current], current_func);
  }

void selected_entity_view_draw(entt::registry & r, entt::entity & selection) {
  ImGui::Begin("SelectedEntity");
  DrawableComponent & dc = r.get<DrawableComponent>(selection);
  NameComponent & nc = r.get<NameComponent>(selection);
  ImGui::Text("Name: %s", nc.m_name);
  ImGui::Text("Type: %s", nc.m_type);
  ImGui::Text("VAO id: %d", dc.m_vao);
  ImGui::Text("Shader id: %d", dc.m_shader);
  ImGui::Text("Vertex count: %d", dc.m_vert_count);

  if (ImGui::ColorEdit3("Color", &dc.m_color.r, ImGuiColorEditFlags_DisplayHex |
                        ImGuiColorEditFlags_InputRGB |
                        ImGuiColorEditFlags_NoAlpha)) {
  }
  ImGui::Checkbox("Wireframe", &dc.m_show_wireframe);

  RotationComponent & rc = r.get<RotationComponent>(selection);
  ModelComponent & mc = r.get<ModelComponent>(selection);
  ImGui::Text("Rotation");

  static bool x = (bool)rc.axis.x, y = (bool)rc.axis.y, z = (bool)(rc.axis.z);
  ImGui::Checkbox("X", (bool*)&x);
  ImGui::Checkbox("Y", (bool*)&y);
  ImGui::Checkbox("Z", (bool*)&z);
  rc.axis.x = x;
  rc.axis.y = y;
  rc.axis.z = z;

  float degrees = rc.radians *180.f/3.14159;
  ImGui::SliderFloat("degrees", &degrees, 0.f, 360.f, "%f");
  rc.radians= degrees*3.14159/180.f;

  // yeah, about that..........
  ImGui::Text("%.2f %.2f %.2f %.2f\n%.2f %.2f %.2f %.2f\n%.2f %.2f %.2f %.2f\n%.2f %.2f %.2f %.2f\n",
            mc.matrix[0][0], mc.matrix[0][1], mc.matrix[0][2], mc.matrix[0][3],
            mc.matrix[1][0], mc.matrix[1][1], mc.matrix[1][2], mc.matrix[1][3],
            mc.matrix[2][0], mc.matrix[2][1], mc.matrix[2][2], mc.matrix[2][3],
            mc.matrix[3][0], mc.matrix[3][1], mc.matrix[3][2], mc.matrix[3][3]
              );

    ImGui::End();
}
