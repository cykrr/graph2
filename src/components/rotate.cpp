#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "components/rotation.hpp"
#include "components/model.hpp"

void rotate_model(ModelComponent & mc, const RotationComponent & rc) {
        if(rc.axis.x + rc.axis.y + rc.axis.z)
          mc.matrix = glm::rotate(mc.matrix, rc.radians, rc.axis);
}
