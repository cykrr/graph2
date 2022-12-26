#ifndef SHADER_COMPONENT_H
#define SHADER_COMPONENT_H
class ShaderComponent
{
public:
  ShaderComponent() = default;
  ShaderComponent(ShaderComponent &&) = default;
  ShaderComponent(const ShaderComponent &) = default;
  ShaderComponent &operator=(ShaderComponent &&) = default;
  ShaderComponent &operator=(const ShaderComponent &) = default;
  ~ShaderComponent() = default;

private:
  
};
#endif
