#ifndef ELEMENT_H
#define ELEMENT_H
#include "glad/glad.h"
#include <cstddef>
class Element {
    public:
        Element();
        Element(int x, int y, int w, int h);
        size_t vertices = 0;
        size_t indices = 0;
        size_t dim = 0;
        int x, y, w, h;
        virtual void draw(){};
        virtual ~Element(){};
};
#endif
