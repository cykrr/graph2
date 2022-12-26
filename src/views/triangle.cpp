#include "views/triangle.hpp"
#include "shaders.hpp"

float Triangle::vertices[] =  {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

Triangle::Triangle() : Drawable("main")
{
  this->model = glm::mat4(1.f);

  vao = new VAO();
  vbo = new VBO(BufferType::array_buffer);

  vao->bind();
  vbo->bind_buffer();
  vbo->send_data(sizeof(vertices), vertices, GL_STATIC_DRAW);

  vao->set_vertex_attr_ptr(0, 3, GL_FLOAT, 3*sizeof(float), NULL);
  vao->enable_vertex_attr_array(0);

  vbo->unbind();
  vao->unbind();
}

void 
Triangle::draw()
{
  this->shader->use();
  this->shader->setMat4("m", this->model);
  vao->bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);
}


