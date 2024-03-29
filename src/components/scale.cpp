#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "components/scale.hpp"
#include "components/model.hpp"

void scale_model(ModelComponent & mc, const ScaleComponent & rc) {
        if(rc.axis.x + rc.axis.y + rc.axis.z)
          mc.matrix = glm::scale(mc.matrix, rc.axis);
          // mc.matrix = glm::scale(glm::identity<glm::mat4>(), rc.axis);
}
