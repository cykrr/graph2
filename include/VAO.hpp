#ifndef VAO_H
#define VAO_H
#include <cstddef>
class VAO {
  public:
    unsigned int get_id() const;
    VAO(unsigned int vao) {this->id = vao;}
    VAO();
    ~VAO();
    void enable_vertex_attr_array(const int idx);
    void disable_vertex_attr_array(const int idx);

    /** @brief Define an array of generic vertex attribute data
     *
     *  @param index Specifies the index of the generic vertex
     *  attribute to be modified.
     *
     *  @param size Specifies the number of components per generic vertex
     *  attribute. Must be 1, 2, 3, 4. Additionally, the symbolic constant
     *  GL_BGRA is accepted by glVertexAttribPointer. The initial value is 4.
     *
     *  @param type Data type of the components
     *  */

    void set_vertex_attr_ptr(unsigned int index, int size, 
                             unsigned int gl_type, size_t stride,
                             const void * ptr);
    void bind();
    static void unbind();
  private:
    unsigned int id;
};
#endif
