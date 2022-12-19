#include "util/color.hpp"

namespace gl {
  extern void clear_color(const Color & color);

  enum Bits {
    depth_buffer = GL_DEPTH_BUFFER_BIT,
    color_buffer = GL_COLOR_BUFFER_BIT,
  };

}
