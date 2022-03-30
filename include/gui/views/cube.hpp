#ifndef CUBE_H
#define CUBE_H
#include "gui/element.hpp"
class Cube : public Element {
    public:
    Cube();
    void draw();
};

extern float cubeVertices[];
#endif
