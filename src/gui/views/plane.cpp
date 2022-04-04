#include "gui/views/plane.hpp"

Plane::Plane() {
    this->program = new Program("plane");
    this->vertices = 18;
    this->indices = 0;
    this->dim = 3;
}

float Plane::array[18] =  { 
    -1.f, 1.f, 0.f,
    1.f, 1.f, 0.f,
    -1.f, -1.f, 0.f,
    -1.f, -1.f, 0.f,
    1.f, -1.f, 0.f,
    1.f, 1.f, 0.f,
};

void Plane::draw() {
    this->program->use();
    glBufferSubData(GL_ARRAY_BUFFER, 
            0, vertices * dim * sizeof(float), this->array);

    glDrawArrays(GL_TRIANGLES, 0, vertices/dim);
}
