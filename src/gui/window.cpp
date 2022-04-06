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

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouseCallback);



    if(!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress)
    ){
        std::cout << "Error loading GLAD\n";
    }

    glEnable(GL_DEPTH_TEST);
    return window;
}
