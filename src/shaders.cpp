#include "shaders.hpp"

std::map<std::string, Program*> Shaders::programs;

Program *
Shaders::get_shader(std::string shader_name)
{
  std::map<std::string,Program *>::iterator it = programs.find(shader_name);
  Program * program;
  if(it != programs.end())
  {
    //element found;
    program = it->second;
  } else {
    program = new Program(shader_name);
    programs[shader_name] = program;
  }
  return program;
}
