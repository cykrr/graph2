#include "VBO.hpp"
#include "glad/glad.h"

VBO::VBO()
{
  glGenBuffers(1, &this->id);
}

VBO::VBO(BufferType buffer_type)
{
  glGenBuffers(1, &this->id);
  this->buffer_type =  buffer_type;
}

void
VBO::bind_buffer()
{
  glBindBuffer(buffer_type, this->id);
}

void
VBO::send_data(size_t size, void *arr, GLenum draw_config)
{
  glBufferData(this->buffer_type, size, arr, draw_config);
}

VBO::~VBO() {
  glDeleteBuffers(1, &this->id);
}

void
VBO::unbind()
{
  glBindBuffer(this->buffer_type, 0);
}
