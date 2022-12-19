#include "wrappers/gl.hpp"
namespace gl {
void clear_color(const Color & color) {
  glClearColor((float)color.r/0xff, (float)color.g/0xff,
               (float)color.b/0xff, (float)color. a/0xff);
}
}
