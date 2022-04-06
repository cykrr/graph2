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
#include "gui/views/3drect.hpp"
#include "gui/views/plane.hpp"

#include "util.hpp"

void lookUpJoystick();

int main() {
    GLFWwindow *window = initGLFW();

    Renderer *renderer = new Renderer();

    lookUpJoystick();

    renderer->program->use();

    Cam3D camm;

    renderer->setCam3d(camm);

    glfwSetWindowUserPointer(window, renderer);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int w, int h){
            static_cast<Renderer*>(glfwGetWindowUserPointer(window))
            ->update(w, h);
            });

    renderer->add(new Cube());
    renderer->add(new Plane());
    renderer->prepare();

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );



    while(!glfwWindowShouldClose(window)){

        updateTime();

        glClearColorHex("#202020");
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        processInput(window, renderer);



        static_cast<Plane*>(renderer->childs[1])->program->use();
        static_cast<Plane*>(renderer->childs[1])->program->setMat4("p", renderer->cam3d->projection);
        static_cast<Plane*>(renderer->childs[1])->program->setMat4("v", renderer->cam3d->view);
        renderer->childs[1]->draw();

        renderer->program->use();
        renderer->program->setMat4("m", glm::mat4(1.f));

        renderer->program->setMat4("m", glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(1.f, 2.f, 3.f)));

        renderer->childs[0]->draw();

        glBindVertexArray(renderer->VAO);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glfwTerminate();

    return 0;
}
void lookUpJoystick() {
    int joystickPresent = glfwJoystickPresent(GLFW_JOYSTICK_2);
    if (joystickPresent) {
        std::cout << "1:" << 
            glfwGetJoystickName(GLFW_JOYSTICK_1) << '\n';
        std::cout << "2:" << 
            glfwGetJoystickName(GLFW_JOYSTICK_2) << '\n';
        std::cout << "3:" << 
            glfwGetJoystickName(GLFW_JOYSTICK_3) << '\n';
        std::cout << "4:" << 
            glfwGetJoystickName(GLFW_JOYSTICK_4) << '\n';
        
    }

}
