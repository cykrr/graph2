#ifndef VIEW_PROJ_COMPONENT_H
#define VIEW_PROJ_COMPONENT_H
#include "glm/mat4x4.hpp"
struct VPComponent
{

  glm::mat4 m_VP;
  VPComponent() = default;
  VPComponent(VPComponent &&) = default;
  VPComponent(const VPComponent &) = default;
  ~VPComponent() = default;
  operator const glm::mat4 &() {
      return m_VP;
    }
  
};
#endif
