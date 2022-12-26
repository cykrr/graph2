#include "shaders.hpp"

std::map<std::string, unsigned int> Shaders::programs;

unsigned int
Shaders::get_shader(std::string shader_name)
{
  std::map<std::string,unsigned int>::iterator it = programs.find(shader_name);
  unsigned int program_id;
  if(it != programs.end())
  {
    //element found;
    program_id = it->second;
  } else {
    printf("%s no existe, creando\n", shader_name.c_str());
    Program p(shader_name);
    programs[shader_name] = p.get_id();
    program_id = p.get_id();
  }
  return program_id;
}
