#include <iostream>

#include <GLFW/glfw3.h>

#include "ft2mm.hpp"

int main() {
    FreeType2::Library ft2lib;
    FreeType2::Face face(ft2lib, "fonts/Cantarell.otf", 0);
    face.setSize(0, 48);


}
