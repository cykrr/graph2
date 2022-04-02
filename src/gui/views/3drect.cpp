#include "gui/views/3drect.hpp"
Rect3d::Rect3d() {
    glm::vec3 arr[] = {
        glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(1.f, 0.f, 0.f),
        glm::vec3(0.f, 1.f, 0.f),
        glm::vec3(1.f, 1.f, 0.f)
    };
    this->vertices = 4;
    this->indices = 6;
    this->dim = 3;
}

void Rect3d::draw() {
    float vertexArr[] = {
        0.f, 0.f, 0.f,
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        1.f, 1.f, 0.f
        
    };
    unsigned int indicesArr[] = {
        0, 1, 3,
        0, 3, 2
    };
    
    glBufferSubData(GL_ARRAY_BUFFER, 0,
            this->vertices*sizeof(float) * this->dim,
            vertexArr);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
            this->indices*sizeof(unsigned int),
            indicesArr);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

