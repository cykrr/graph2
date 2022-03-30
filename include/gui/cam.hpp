#ifndef CAM_H
#define CAM_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

class Camera {
    public:
        glm::mat4 matrix;
        virtual void update(int w, int h){}
        virtual ~Camera(){};
};
class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(int w, int h);
        glm::mat4 matrix;
        void update(int w, int h);
};
#endif
