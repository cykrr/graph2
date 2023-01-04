#include "imgui.h"
#include "components/gui.hpp"

#include "components/mesh.hpp"

#include "components/rotate.hpp"
#include "components/scale.hpp"
#include "components/translate.hpp"

#include "gui/elements/matrix.hpp"
#include "entities/cube.hpp"
#include "entities/triangle.hpp"

#include "gui/views/entity_v.hpp"
#include "gui/views/component.hpp"

using namespace Descriptors;
namespace Views::VEntity {

typedef struct Entity (*entity_fn_t)(entt::registry &);
std::tuple<const char *, entity_fn_t> entity_type_picker_draw(entt::registry &);

void create(entt::registry & r, struct Entity & selection, bool & selected)
{
  ImGui::Text("Create entity:");
  // grab primitive and it's name
  std::tuple<const char *, entity_fn_t> entity_desc = 
                                              entity_type_picker_draw(r);

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
    // Fill it's components
    GUIComponent nc(buf,  ent_type_str, components);
    selection.emplace<GUIComponent>(nc);

    MeshComponent & c = selection.get<MeshComponent>();
    c.m_color = color;
  }
}

void pick(entt::registry &r, struct Entity & selection, bool &selected)
{
  ImGui::Text("Entity Picker");
  if (ImGui::BeginListBox("##Entity Picker")) {
    auto view = r.view<GUIComponent>();
    for (const entt::entity & ent : view) {
      GUIComponent & name = r.get<GUIComponent>(ent);

      bool is_selected = ImGui::Selectable(name.m_name,
                                           ent == selection.ent);
      if (ImGui::BeginPopupContextItem())
      {
        ImGui::Text("sakjdsakjd");
        ImGui::EndPopup();
      }
      if (is_selected)  {
        selection.ent = ent;
        selected = true;
      }
    }
    ImGui::EndListBox();
  }
}

void view(struct Entity & selection) {
  ImGui::Begin("SelectedEntity");

  Views::Component::create(selection);

  GUIComponent & nc = selection.get<GUIComponent>();
  static int selected_component = false;
  ImGui::Text("Components");
  ImGui::ListBox("##Components", &selected_component,
                 [](void *data, int idx, const char ** out_text) {
                   Components::m_enum pos = ((Components::m_enum*)data)[idx];
                   *out_text = Components::m_name[pos];
                   return true;
                 }, &nc.components[0], nc.components.size());

  MeshComponent & dc = selection.get<MeshComponent>();
  ImGui::Text("Name: %s", nc.m_name);
  Components::m_enum component = nc.components[selected_component];

  switch (component) {
    case Components::TranslateComponent: {

      TranslateComponent & s = 
        selection.reg.get<TranslateComponent>(selection.ent);

      ImGui::Text("Scale");
      ImGui::InputFloat3("##Scale", &s.position.x, "%.2f");
      break;
    }
    case Components::ScaleComponent: {
      ScaleComponent & s = selection.reg.get<ScaleComponent>(selection.ent);
      ImGui::Text("Scale");
      ImGui::InputFloat3("##Scale", &s.axis.x, "%.2f");
      break;
    }
    case Components::AnimationComponent: {
      AnimationComponent & ac = selection.get<AnimationComponent>();
      ImGui::Text("Animations");
      ImGui::BeginListBox("##Animations");
      int i = 0;
      for (std::vector<Animation> & g : ac.groups) {
          
          ImGui::Selectable("Group [%d]", i);
        for (Animation &a : g) {
          
        }
        ++i;
      }

      ImGui::EndListBox();
      break;
    }

    case Components::MeshComponent:
      ImGui::Text("Type: %s", nc.m_type);
      ImGui::Text("Drawable Component");
      ImGui::Text("VAO id: %d", dc.m_vao);
      ImGui::Text("Vertex count: %d", dc.m_vert_count);
      if (ImGui::ColorEdit3("Color", &dc.m_color.r,
                            ImGuiColorEditFlags_DisplayHex |
                            ImGuiColorEditFlags_InputRGB   |
                            ImGuiColorEditFlags_NoAlpha)) {
      }
      ImGui::Checkbox("Wireframe", &dc.m_show_wireframe);
      break;
    case Components::ModelComponent:
      ImGui::Text("Model Matrix:");

      {
      ModelComponent & mc = selection.get<ModelComponent>();
      // yeah, about that..........
      Views::matrix(mc.matrix);
      }
      break;
    case Components::ShaderComponent:{
      ShaderComponent & s = selection.get<ShaderComponent>();
      ImGui::Text("Shader ID: %d", s.shader);
      break;
    }
    case Components::RotateComponent:{

      static RotateComponent  rc({glm::vec3(0.f), 0.f}); 
      ModelComponent & mc = selection.get<ModelComponent>();
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
  }

  ImGui::End();
}

std::tuple<const char *, entity_fn_t>
entity_type_picker_draw(entt::registry & r)
{
  static const char * items_str[] = {"Triangle", "Cube"};

  const entity_fn_t items_func[10] = {create_triangle, create_cube};
  static entity_fn_t current_func = NULL;

  static int item_current = 0;

  ImGui::Text("Type");
  ImGui::Combo("##Type", &item_current, items_str, IM_ARRAYSIZE(items_str));
  current_func = items_func[item_current];

  return std::tuple<const char *, entity_fn_t>
                        (items_str[item_current], current_func);
}

}
