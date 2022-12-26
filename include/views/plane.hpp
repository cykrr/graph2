#ifndef PLANE_H
#define PLANE_H
#include "element.hpp"
#include "program.hpp"

class Plane : public Element {
    static float array[18];
    public:
        Plane();
        void draw();
        Program *program;
};
#endif
