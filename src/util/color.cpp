#include "util/color.hpp"
#include <stdio.h>

void glClearColorHex(std::string fmt)
{
    int b,c,d;
    sscanf(fmt.c_str(), "#%02x%02x%02x", &b, &c, &d);
    glClearColor((float)b/0xff,
            (float)c/0xff, 
            (float)d/0xff, 
            1.0f);
}

Color::Color(const std::string & hex) {
  sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
  a = 0xff;
}
Color::Color(int r, int g, int b) {
  this->r = r, this->g = g, this->b = b;
}

Color::Color(int r, int g, int b, int a) : Color(r, g, b) {
  this->a = a;
}

void Color::set_alpha(float a) {
  this->a = a;
}
