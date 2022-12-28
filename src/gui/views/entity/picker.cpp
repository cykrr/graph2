#include <entt/entity/registry.hpp>
#include "imgui.h"
#include "components/name.hpp"
#include "gui/views/entity.hpp"
void entity_picker(entt::registry &r, entt::entity & selection, bool &selected)
{
  if (ImGui::BeginListBox("Entity Picker")) {
    auto view = r.view<NameComponent>();
    for (const entt::entity & ent : view) {
      NameComponent & name = r.get<NameComponent>(ent);
      if (ImGui::Selectable(name.m_name , ent == selection))  {
        selection = ent;
        selected = true;
      }
    }
    ImGui::EndListBox();
  }
}
