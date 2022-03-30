#ifndef RECT_H
#define RECT_H
#include "gui/element.hpp"
class Rectangle : public Element {
    public:
        Rectangle(int x, int y, int w, int h);
        void draw();
};
#endif
