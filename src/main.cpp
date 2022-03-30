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

#include "util.hpp"


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
     0.5f,  0.5f, -3.0f,  // top right
     0.5f, -0.5f, -3.0f,  // bottom right
    -0.5f, -0.5f, -3.0f,  // bottom left
    -0.5f,  0.5f, -3.0f   // top left 
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
    glEnable(GL_DEPTH_TEST);

    Renderer *renderer = new Renderer();
    renderer->program->use();

    renderer->w = 800; renderer->h = 800;

//    Camera cam = OrthographicCamera(renderer->w, renderer->h);
    Camera cam = MovingCamera(renderer->w, renderer->h);
    renderer->setCam(cam);

    glfwSetWindowUserPointer(window, renderer);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int w, int h){
            static_cast<Renderer*>(glfwGetWindowUserPointer(window))
            ->update(w, h);
            });

    renderer->add(new Cube());
    renderer->add(new Rectangle(100 , 100, 100, 100));
    renderer->prepare();


    glm::mat4 view(1.0f), projection(1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glm::vec3 pos(0.f, 0.f, 3.f), 
        front(0.f, 0.f, -1.f),
        up(0.f, 1.f, 0.f);
    const float speed = 2.5f;

    while(!glfwWindowShouldClose(window)){

        glm::mat4 model(1.0f);
        processInput(window);
        updateTime();
        glClearColorHex("#202020");
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        renderer->program->use();
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            pos += front * speed * dt;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            pos -= front * speed * dt;
        }

        view = glm::lookAt(pos, 
                pos + front,
                up);

        projection = glm::perspective(glm::radians(45.0f), 
                (float)renderer->w / (float)renderer->h, 0.1f, 100.0f);


//        model = glm::rotate(model, (float)(currentTime),
 //               glm::vec3(2.f, 1.0f, 0.0f));


        glm::mat4 MVP = projection * view * model;

        glBindVertexArray(renderer->VAO);


        renderer->program->setMat4("mvp", MVP);

        renderer->childs[0]->draw();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glfwTerminate();

    return 0;
}
