#ifndef SHADER_COMPONENT_H
#define SHADER_COMPONENT_H
struct ShaderComponent
{
  ShaderComponent() = default;
  ShaderComponent(ShaderComponent &&) = default;
  ShaderComponent(const ShaderComponent &) = default;
  ShaderComponent &operator=(ShaderComponent &&) = default;
  ShaderComponent &operator=(const ShaderComponent &) = default;
  ~ShaderComponent() = default;
  unsigned int shader;
};
#endif
