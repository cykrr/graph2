#include <iostream>
#include <stdint.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/glad.h"


#include "gui/color.hpp"
#include "gui/window.hpp"
#include "gui/program.hpp"
#include "gui/renderer.hpp"
#include "gui/input.hpp"
#include "gui/cam.hpp"
#include "gui/views/rectangle.hpp"
#include "gui/views/cube.hpp"

int Swidth = 0; 
int Sheight = 0;

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Swidth = width;
    Sheight = height;
}

void draw2(){
    float arr[12] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };  

    unsigned int arr2[6] = {
        0, 1, 3, 1, 2, 3
    };

    glBufferSubData(GL_ARRAY_BUFFER, 
            0, 12 * sizeof(float), 
            arr);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 
            0, 6 * sizeof(unsigned int), 
            arr2);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
}

int main() {
    GLFWwindow *window = initGLFW();
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glEnable(GL_DEPTH_TEST);

    Renderer *renderer = new Renderer();
    renderer->program->use();

    renderer->add(new Cube());
    renderer->prepare();

    Swidth = 800; Swidth = 800;

    glm::mat4 view(1.0f), projection(1.0f), model(1.0f);
    while(!glfwWindowShouldClose(window)){

        processInput(window);
        glClearColorHex("#202020");
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        renderer->program->use();


        model = glm::rotate(model, (float)(glfwGetTime()),
                glm::vec3(1.0f, 1.0f, 0.0f));

        glm::mat4 MVP = projection * view * model;

        renderer->program->use();

        renderer->program->setMat4("mvp", MVP);
        printf("%f\n",  MVP[0][0] );

        glBindVertexArray(renderer->VAO);
        renderer->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glfwTerminate();

    return 0;
}
