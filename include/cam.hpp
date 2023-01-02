#ifndef CAM_H
#define CAM_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

#include "util.hpp"

class Camera {
    public:
        glm::mat4 matrix = glm::mat4(1.f);
        virtual void update(int w, int h){
          // printf("notin\n");
        };
        Camera(){}
        virtual ~Camera(){};
};
class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(int w, int h);
        void update(int w, int h) override;
};

class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(int w, int h);
        PerspectiveCamera();
        static glm::vec3 vUp, vFront;
        glm::vec3 pos, direction, right;
        float yaw = -90.0f, pitch = 0, roll = 0;
        float speed;

        void update(int w, int h) override;

        void moveFront();
        void moveBack();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
};

class Cam3D {
    public:
        Cam3D();
        glm::vec3 pos, direction, front;

        const static glm::vec3 up;
        static constexpr float speed = 2.5f;

        glm::mat4 view, projection;

        bool firstMouse = 1;
        float lastX = 400, lastY = 400;

        float yaw = -90.f, pitch = 0, roll = 0;

        float sensitivity = 0.1f;

        void update(int w, int h);
        void moveFront();
        void updateDirection();
};

void update_orthographic_camera(Camera &cam, int w, int h);

#endif
