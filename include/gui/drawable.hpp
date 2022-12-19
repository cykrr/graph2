#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "VAO.hpp"
#include "VBO.hpp"
#include "program.hpp"
class Drawable {
  public: 
  Drawable(const std::string & shader_name);
  // maybe not virtual
  virtual void rotate(glm::vec3 & axis, float radians);
  virtual void translate(const glm::vec3 & offset);
  virtual void scale(glm::vec3 & axis);
  virtual void reset();

  // virtual void update() = 0;
  virtual void draw() = 0;
  virtual ~Drawable(){};

  const char * name = "Drawable";

protected:
  VAO *vao = NULL;
  VBO *vbo = NULL;
  glm::mat4 model = glm::mat4(1.0f);

  glm::vec3 position; 
  Program *shader = NULL;
};
#endif
