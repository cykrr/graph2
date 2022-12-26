#ifndef NAME_COMPONENT_H
#define NAME_COMPONENT_H
#include <string>
struct NameComponent
{
  NameComponent() = default;
  NameComponent(NameComponent &&) = default;
  NameComponent(const NameComponent &) = default;
  ~NameComponent() = default;
  std::string name;
};

#endif
