#ifndef INSTANCE_H
#define INSTANCE_H
#include "glm/vec3.hpp"
template <class T> class Instance {
public:
  void set_position(glm::vec3 &position);
  const glm::vec3 &get_position();

private:
  glm::vec3 position;
  glm::vec3 scale;
  // DrawableType type;
};
#endif
