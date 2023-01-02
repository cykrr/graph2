#include "gui/views/entity.hpp"
#include "imgui.h"
#include "components/gui.hpp"

#include "components/mesh.hpp"

#include "components/rotate.hpp"
#include "components/scale.hpp"
#include "components/translate.hpp"

#include "gui/elements/matrix.hpp"
#include "entities/cube.hpp"
#include "entities/triangle.hpp"

namespace Views::Entity {
void pick(entt::registry &r, entt::entity & selection, bool &selected)
{
  ImGui::Text("Entity Picker");
  if (ImGui::BeginListBox("##Entity Picker")) {
    auto view = r.view<GUIComponent>();
    for (const entt::entity & ent : view) {
      GUIComponent & name = r.get<GUIComponent>(ent);
      if (ImGui::Selectable(name.m_name , ent == selection))  {
        selection = ent;
        selected = true;
      }
    }
    ImGui::EndListBox();
  }
}

void view(entt::registry & r, entt::entity & selection) {
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
      Views::matrix(mc.matrix);
      }
      break;
    case Components::ShaderComponent:{
      ShaderComponent & s = r.get<ShaderComponent>(selection);
      ImGui::Text("Shader ID: %d", s.shader);
      break;
    }
    case Components::RotateComponent:{

      static RotateComponent  rc({glm::vec3(0.f), 0.f}); 
      ModelComponent & mc = r.get<ModelComponent>(selection);
      ImGui::Text("Rotate");
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

typedef  entt::entity(*entity_fn_t)(entt::registry &);

std::tuple<const char *, entity_fn_t> entity_type_picker_draw(entt::registry &);



void create(entt::registry & r, entt::entity & selection, bool & selected)
{
  ImGui::Text("Create entity:");
  // grab primitive and it's name
  std::tuple<const char *, entity_fn_t> entity_desc =  entity_type_picker_draw(r);

  // draw color
  static Color color("#ffffff");
  ImGui::Text("Color");
  ImGui::ColorEdit3("##Color", &color.r, 
                    ImGuiColorEditFlags_DisplayHex |
                    ImGuiColorEditFlags_InputRGB
                    );

  static char buf[50] = "";
  ImGui::Text("Name");
  if (
    ImGui::InputText("##name", buf, 50,ImGuiInputTextFlags_EnterReturnsTrue) &&
    strlen(buf) != 0 
  ) {
    // get primitive type
    const char * ent_type_str = std::get<0>(entity_desc);

    // get selected fn and call it to get the ent
    selection = std::get<1>(entity_desc)(r); 
    selected = true;

    std::vector<Components::m_enum> components;
    components.push_back(Components::MeshComponent);
    components.push_back(Components::ShaderComponent);
    components.push_back(Components::ModelComponent);
    components.push_back(Components::RotateComponent);
    // Fill it's components
    GUIComponent nc(buf,  ent_type_str, components);
    r.emplace<GUIComponent>(selection, nc);
    r.emplace<RotateComponent>(selection, RotateComponent({glm::vec3(1.f), 0.f}));

    MeshComponent & c = r.get<MeshComponent>(selection);
    c.m_color = color;
  }
}

std::tuple<const char *, entity_fn_t> entity_type_picker_draw(entt::registry & r)
{
  static const char * items_str[] = {"Triangle", "Cube"};

  const entity_fn_t items_func[10] = {create_triangle, create_cube};
  static entity_fn_t current_func = NULL;

  static int item_current = 0;

  ImGui::Text("Type");
  ImGui::Combo("##Type", &item_current, items_str, IM_ARRAYSIZE(items_str));
  current_func = items_func[item_current];
  return std::tuple<const char *, entity_fn_t>(items_str[item_current], current_func);
}

}
