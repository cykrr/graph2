#ifndef VBO_H
#define VBO_H
#include "buffer_type.hpp"
#include <cstddef>
class VBO {
  public:
    unsigned int get_id() const;
    VBO();
    VBO(BufferType buffer_type);
    ~VBO();
    void bind_buffer();
    void send_data(size_t size, void *arr, GLenum draw_config);
    void unbind();
  private:
    unsigned int id;
    BufferType buffer_type;
};
#endif

