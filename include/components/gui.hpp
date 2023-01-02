#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H
#include <string.h>
#include <vector>
#include "gui/desc/components.hpp"
// Allow entities to be identified by GUI
struct GUIComponent
{
  char m_name[50];
  char m_type[50];
  std::vector<Components::m_enum> components;

  GUIComponent() = default;
  GUIComponent(GUIComponent &&) = default;
  GUIComponent(const GUIComponent &) = default;
  ~GUIComponent() = default;
  GUIComponent(char *name, const char *type, std::vector<enum Components::m_enum> components) :
    components(components) {
      strcpy(m_name, name); strcpy(m_type, type);
      
  }

};

#endif
