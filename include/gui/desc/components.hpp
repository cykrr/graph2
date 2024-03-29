#ifndef GUI_COMPONENTS_H
#define GUI_COMPONENTS_H
namespace Descriptors {

namespace Components {

enum m_enum {
  NoComponent = 0,
  MeshComponent,
  AnimationComponent,
  ScaleComponent,
  TranslateComponent,
  RotateComponent,
  ModelComponent,
  ShaderComponent,
};

static const char * m_name [] {
 "None",
 "Mesh",
 "Animation",
 "Scale",
 "Translate",
 "Rotate",
 "Model",
 "Shader",
};



}
}
#endif
