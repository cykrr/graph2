#ifndef GUI_COMPONENTS_H
#define GUI_COMPONENTS_H
namespace Components {

enum m_enum {
  NoComponent = 0,
  DrawableComponent,
  AnimationComponent,
  ScaleComponent,
  TranslateComponent,
  RotateComponent,
  ModelComponent,
};

static const char * m_name [] {
 "NoComponent",
 "DrawableComponent",
 "AnimationComponent",
 "ScaleComponent",
 "TranslateComponent",
 "RotateComponent",
 "ModelComponent",
};



}
#endif
