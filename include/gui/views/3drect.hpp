#ifndef RECT3_h
#define RECT3_h
#include "gui/element.hpp"
#include "glm/vec3.hpp"

class Rect3d : public Element {
    public:
        Rect3d();
        glm::vec3 arr[];
        void draw();
};
#endif
