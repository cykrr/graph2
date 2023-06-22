#ifndef PROGRAM_H
#define PROGRAM_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Program {
    private:
        unsigned int id;
        std::string shader_name;
    public:
        const std::string & get_shader_name() {
          return this->shader_name;    
        }
        unsigned int get_id() {return this->id;}
        Program(std::string name);
        Program(unsigned int id) {this->id = id;}
        ~Program(){}
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        static void setVec4_id(unsigned int id, const std::string &name, const glm::vec4 &value);
        void setVec4(const std::string &name, float x, float y, float z, float w);
        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        static void setMat4_id(unsigned int id, const std::string &name, const glm::mat4 &mat);
};
#endif
