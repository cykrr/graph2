#include "gui/views/3drect.hpp"
Rect3d::Rect3d() {
    this->vertices = 4;
    this->indices = 6;
    this->dim = 3;
}

void Rect3d::draw() {
    float vertexArr[] = {
        -1.f, 1.f, 0.f,
        1.f, 1.f, 0.f,
        -1.f, -1.f, 0.f,
        1.f, -1.f, 0.f,
        
    };
    unsigned int indicesArr[] = {
        0, 1, 2,
        2, 3, 1 
    };
    
    glBufferSubData(GL_ARRAY_BUFFER, 0,
            this->vertices*sizeof(float) * this->dim,
            vertexArr);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
            this->indices*sizeof(unsigned int),
            indicesArr);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

