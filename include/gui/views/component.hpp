#ifndef COMP_VIEW
#define COMP_VIEW
#include "gui/views.hpp"
#include "entity.hpp"
#include "imgui.h"
#include "gui/desc/components.hpp"
#include "components/animation.hpp"
#include "components/scale.hpp"
#include "components/translate.hpp"
#include "components/gui.hpp"
namespace Views{
namespace Component {

static void create(Entity & e) {
  ImGui::Text("Create Component");
  static int current_item = 1;
  ImGui::Combo("##Create_component", &current_item, &Descriptors::Components::m_name[0], IM_ARRAYSIZE(Descriptors::Components::m_name));
  if (ImGui::Button("Create")) {
    switch (current_item) {
      case Descriptors::Components::TranslateComponent: {
        e.emplace<TranslateComponent>(TranslateComponent());
        e.get<GUIComponent>().components.push_back((Descriptors::Components::m_enum)current_item);

        break;
      }
      case Descriptors::Components::ScaleComponent: {
        e.emplace<ScaleComponent>(ScaleComponent());
        e.get<GUIComponent>().components.push_back((Descriptors::Components::m_enum)current_item);
        break;
      }
      case Descriptors::Components::AnimationComponent: {
        e.emplace<AnimationComponent>(AnimationComponent());
        e.get<GUIComponent>().components.push_back((Descriptors::Components::m_enum)current_item);
        break;
      }
    }
  }
}

} 
} 
#endif

