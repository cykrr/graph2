#include "program.hpp"
// #include <GL/glew.h>
#include <glad/glad.h>

void Program::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void Program::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Program::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(id, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Program::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Program::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void Program::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Program::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void Program::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}

void Program::setVec4_id(unsigned int id, const std::string &name, const glm::vec4 &value)
{ 
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Program::setVec4(const std::string &name, float x, float y, float z, float w) 
{ 
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void Program::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Program::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Program::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Program::setMat4_id(unsigned int id, const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void checkErrors(GLuint id, std::string type)
{
    GLint success = 0; static GLchar log[2048];
    if(type != "program") {

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 2048, NULL, log);
            std::cout << "Error compiling " << type << "\n" 
                << log << '\n';
        } 
        printf("Success\n");
    } else  {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
       if(!success){
           glGetProgramInfoLog(id, 2048, NULL, log);
           std::cout << log << '\n';
       }
   }
    if (!success) {
        exit(1);
    }
}

void Program::use()
{
    glUseProgram(this->id);
}

Program::Program(std::string name)
{
    this->shader_name = name;
    GLuint vertex, frag;

    std::ifstream vertexFile, fragFile;
    std::stringstream vertexStream, fragStream;
    std::string tmp;

    const char *src;

    vertexFile.open("./res/shaders/" + name + ".vert");
    fragFile.open("./res/shaders/" + name + ".frag");

    if (!(vertexFile && fragFile)){
        std::cout << "Shader " + name + " not found\n";
        exit(1);
    }

    vertexStream << vertexFile.rdbuf();
    fragStream << fragFile.rdbuf();

    vertexFile.close(); fragFile.close();

    tmp = vertexStream.str();
    src = tmp.c_str();
    printf("%s\n", src);

    vertex = glCreateShader(GL_VERTEX_SHADER);
    if (vertex) {
        glShaderSource(vertex, 1, &src, NULL);
        glCompileShader(vertex);
        checkErrors(vertex, "vertex");
    } else {
        printf("no vertex\n");
    }

    tmp = fragStream.str();
    src = tmp.c_str();

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &src, NULL);
    glCompileShader(frag);
    checkErrors(frag, "fragment");

    this->id = glCreateProgram();

    glAttachShader(id, vertex);
    glAttachShader(id, frag);

    glLinkProgram(id);

    checkErrors(id, "program");

    glDeleteShader(vertex);
    glDeleteShader(frag);
}
