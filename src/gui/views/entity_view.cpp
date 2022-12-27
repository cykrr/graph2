#include <entt/entity/registry.hpp>

#include "components/drawable.hpp"
#include "components/name.hpp"

#include "entities/cube.hpp"
#include "entities/triangle.hpp"

#include "gui.hpp"
void GUI::entity_view_draw(entt::registry &r)
{
  ImGui::Begin("Entities");
  ImGui::Text("Create entity:");
  std::tuple<const char *, entity_fn_t> entity_desc =  entity_type_picker_draw(r);
  static Color color("#00ff00");
  // static bool send_color = false;
  if (ImGui::ColorEdit3("Color", &color.r, ImGuiColorEditFlags_DisplayHex |
                        ImGuiColorEditFlags_InputRGB |
                        ImGuiColorEditFlags_NoAlpha)) {
    // send_color = true;

  }

  char buf[50] = "";
  if (
    ImGui::InputText("name", buf, 50,ImGuiInputTextFlags_EnterReturnsTrue) &&
    strlen(buf) != 0 
  ) {
    entt::entity e = std::get<1>(entity_desc)(r);
    const char * n = std::get<0>(entity_desc);
    NameComponent nc(buf,  n);

    m_scene.m_registry.emplace<NameComponent>(e, nc);
    DrawableComponent & c = r.get<DrawableComponent>(e);
    c.m_color = color;
  }

  static entt::entity selection;
  static bool selected = false;
  if (ImGui::BeginListBox("Entities")) {
    auto view = r.view<NameComponent, DrawableComponent>();
    (view.each([](const auto & ent, auto &name, auto &drawable) {
                 if (ImGui::Selectable(name.m_name)) {
                   selected = true;
                   selection = ent;
                 }
               }));
    ImGui::EndListBox();
  }
  ImGui::End();
  if (selected) {
    ImGui::Begin("SelectedEntity");
    DrawableComponent & dc = m_scene.m_registry.get<DrawableComponent>(selection);
    NameComponent & nc = m_scene.m_registry.get<NameComponent>(selection);
    ImGui::Text("Name: %s", nc.m_name); 
    ImGui::Text("Type: %s", nc.m_type); 

    if (ImGui::ColorEdit3("Color", &dc.m_color.r, ImGuiColorEditFlags_DisplayHex |
                          ImGuiColorEditFlags_InputRGB |
                          ImGuiColorEditFlags_NoAlpha)) {
    }

    ImGui::End();
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
