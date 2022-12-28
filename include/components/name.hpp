#ifndef NAME_COMPONENT_H
#define NAME_COMPONENT_H
#include <string.h>
// Allow entities to be identified by GUI
struct NameComponent
{
  NameComponent() = default;
  NameComponent(NameComponent &&) = default;
  NameComponent(const NameComponent &) = default;
  ~NameComponent() = default;
  NameComponent(char *name, const char *type) {strcpy(m_name, name); strcpy(m_type, type);}
  char m_name[50];
  char m_type[50];
};

#endif
