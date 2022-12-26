#include "VAO.hpp"
#include "glad/glad.h"

VAO::VAO()
{
  glGenVertexArrays(1, &this->id);
}

VAO::~VAO()
{
  glDeleteVertexArrays(1, &this->id);
}

unsigned int VAO::get_id() const
{
  return this->id;
}

/** Enables a vertex attribute (VA) . If access to a VA is disabled, it 
 *  will produce a constant value.
 *
 */
void
VAO::enable_vertex_attr_array(const int idx)
{
  glEnableVertexAttribArray(idx);
}

void
VAO::disable_vertex_attr_array(const int idx)
{
  glDisableVertexAttribArray(idx);
}

void
VAO::bind()
{
  glBindVertexArray(this->id);
}

void
VAO::unbind()
{
  glBindVertexArray(0);
}


  void VAO::set_vertex_attr_ptr(unsigned int index, int size, 
                           unsigned int gl_type, size_t stride,
                           const void * ptr)
{
  glVertexAttribPointer(index, size, gl_type, false, stride, ptr);
}
