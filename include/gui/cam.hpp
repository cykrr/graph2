#ifndef CAM_H
#define CAM_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

#include "util.hpp"

class Camera {
    public:
        glm::mat4 mP, mV, mM;
        glm::mat4 matrix;
        virtual void update(int w, int h){}
        virtual ~Camera(){};

        virtual void moveFront(){}
        virtual void moveBack(){}
        virtual void moveUp(){}
        virtual void moveDown(){}
        virtual void moveLeft(){}
        virtual void moveRight(){}
};
class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(int w, int h);
        glm::mat4 matrix;
        void update(int w, int h);
};

class MovingCamera : public Camera {
    public:
        MovingCamera(int w, int h);
        MovingCamera();
        static glm::vec3 vUp, vFront;
        glm::vec3 pos, direction, right;
        float speed;

        void update(int w, int h);

        void moveFront();
        void moveBack();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
};

#endif
