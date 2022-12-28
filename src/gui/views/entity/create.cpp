#include "imgui.h"
#include "util/color.hpp"
#include "entt/entity/registry.hpp"

#include "components/drawable.hpp"
#include "components/name.hpp"

#include "entities/cube.hpp"
#include "entities/triangle.hpp"


#include "gui/views/entity.hpp"

typedef  entt::entity(*entity_fn_t)(entt::registry &);

std::tuple<const char *, entity_fn_t> entity_type_picker_draw(entt::registry &);



void create_entity_draw(entt::registry & r)
{
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
    r.emplace<NameComponent>(e, nc);

    DrawableComponent & c = r.get<DrawableComponent>(e);
    c.m_color = color;
  }
}

std::tuple<const char *, entity_fn_t> entity_type_picker_draw(entt::registry & r)
{
  static const char * items_str[] = {"Triangle", "Cube"};

  const entity_fn_t items_func[10] = {create_triangle, create_cube};
  static entity_fn_t current_func = NULL;

  static int item_current = 0;

  ImGui::Combo("Type", &item_current, items_str, IM_ARRAYSIZE(items_str));
  current_func = items_func[item_current];
  return std::tuple<const char *, entity_fn_t>(items_str[item_current], current_func);
}