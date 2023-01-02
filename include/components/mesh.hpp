#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H
#include "model.hpp"
#include "program.hpp"
#include "VAO.hpp"
#include "components/shader.hpp"
#include "util/color.hpp"
struct MeshComponent
{
  unsigned int  m_vao;
  unsigned int  m_vert_count;
  bool          m_show_wireframe;

  Color m_color;

  MeshComponent(MeshComponent &&) = default;
  MeshComponent(const MeshComponent &) = default;
  ~MeshComponent() = default;
};

extern void draw_component(MeshComponent &, ModelComponent &, ShaderComponent &);

#endif
