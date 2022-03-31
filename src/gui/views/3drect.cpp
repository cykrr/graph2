#include "gui/views/3drect.hpp"
Rect3d::Rect3d() {
    glm::vec3 arr[] = {
        glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(1.f, 0.f, 0.f),
        glm::vec3(0.f, 1.f, 0.f),
        glm::vec3(1.f, 1.f, 0.f)
    };
    this->vertices = 4;
    this->indices = 3;
}

void Rect3d::draw() {
    float vertexArr[] = {
    -0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
    };
    unsigned int indicesArr[] = {
        0, 1, 2
    };
    
    glBufferSubData(GL_ARRAY_BUFFER, 0,
            this->vertices*sizeof(float),
            vertexArr);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
            this->indices*sizeof(unsigned int),
            indicesArr);

//    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

