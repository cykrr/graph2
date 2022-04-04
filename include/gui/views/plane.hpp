#ifndef PLANE_H
#define PLANE_H
#include "gui/element.hpp"
#include "gui/program.hpp"

class Plane : public Element {
    static float array[18];
    public:
        Plane();
        void draw();
        Program *program;
};
#endif
