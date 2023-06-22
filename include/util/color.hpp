#ifndef COLOR_H 
#define COLOR_H
#include "glad/glad.h"
#include <string>
#include "glm/vec4.hpp"
// #include "imgui/imgui.h"
void glClearColorHex(std::string fmt);
class Color : public glm::vec<4, float> {
public:
  Color(const std::string & hex);
  // Color(ImVec4 &c){
  //   this->r = c.x;
  //   this->g = c.y;
  //   this->b = c.z;
  //   this->a = c.w;
  // }

  Color(unsigned int r, unsigned int g, unsigned int b)  {
    this->r = (float)r;
    this->g = (float)g;
    this->b = (float)b;
    this->a = 1.f;
  }

  Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a): Color(r,g,b) {
    this->a = (float)a/0xff;
  }

  void set_alpha(float a);
};

#endif 
