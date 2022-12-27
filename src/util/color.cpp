#include "util/color.hpp"
#include <stdio.h>

Color::Color(const std::string & hex) {
  unsigned int r,g,b;
  sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
  this->r = (float)r/0xff;
  this->g = (float)g/0xff;
  this->b = (float)b/0xff;
  this->a = 1.f;
}

void Color::set_alpha(float a) {
  this->a = a;
}
