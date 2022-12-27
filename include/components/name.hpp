#ifndef NAME_COMPONENT_H
#define NAME_COMPONENT_H
#include <string.h>
struct NameComponent
{
  NameComponent() = default;
  NameComponent(NameComponent &&) = default;
  NameComponent(const NameComponent &) = default;
  ~NameComponent() = default;
  NameComponent(char *name) {strcpy(this->name, name);}
  char name[50];
};

#endif
