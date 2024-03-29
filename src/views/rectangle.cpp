#include "views/rectangle.hpp"
#include <iostream>
Rectangle::Rectangle(int x, int y, int w, int h) : 
    Element(x, y, w, h)
{
    this->vertices = 12;
    this->indices = 12;
    this->dim = 2;
}


void Rectangle::draw(){
    float arr[12] = {
        (float)x + w, (float)y    , 0.f,
        (float)x + w, (float)y + h, 0.f,
        (float)x,     (float)y + h, 0.f,
        (float)x,     (float)y    , 0.f
    };
    unsigned int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };

    glBufferSubData(GL_ARRAY_BUFFER, 
            0, this->vertices * sizeof(float), 
            arr);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 
            0, this->indices * sizeof(unsigned int), 
            indices);
    glDrawElements(GL_TRIANGLES, 6, 
            GL_UNSIGNED_INT, 0);
}
