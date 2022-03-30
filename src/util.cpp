#include "util.hpp"

float currentTime = 0;
float prevTime = 0;
float dt = 0;

void updateTime(){
    currentTime = glfwGetTime();
    dt = currentTime - prevTime;
    prevTime = currentTime;
}
