#ifndef COLOR_H 
#define COLOR_H
#include "glad/glad.h"
#include <string>
void glClearColorHex(std::string fmt);
class Color {
public:
  int r, g, b, a;
  Color(const std::string & hex);
  Color(int r, int g, int b);
  Color (int r, int g, int b, int a);
  void set_alpha(float a);
};

#endif 
