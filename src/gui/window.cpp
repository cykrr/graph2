#include "gui/window.hpp"
GLFWwindow *initGLFW()
{
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(
            300, 300, "Pong", NULL, NULL);

    glfwWindowHint(
            GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(
            GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(
            GLFW_OPENGL_PROFILE, 
            GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);


    if(!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress)
    ){
        std::cout << "Error loading GLAD\n";
    }
    return window;
}
