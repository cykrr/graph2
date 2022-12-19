#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "VAO.hpp"
#include "VBO.hpp"
#include "gui/program.hpp"
#include "gui/drawable.hpp"
class Triangle  : public Drawable {
public:
  Triangle();
  static float vertices[9];  
  void draw() override;
};
#endif
