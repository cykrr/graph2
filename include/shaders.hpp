#ifndef SHADERS_H
#define SHADERS_H
#include "program.hpp"
#include <string>
#include <map>
class Shaders {
public: 
  static Program *get_shader(std::string shader_name);
private:
  static std::map<std::string, Program*> programs;
};
#endif
