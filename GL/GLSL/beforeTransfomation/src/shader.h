#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
class Shader {
public:
  static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType);
  ~Shader();
  
  uint32_t Get() const { return m_shader; }    
private:
  Shader() {} //creator private, For to forbid shader instanse in out of class range
  //for call creator you can use CreateFromFile func.
  bool LoadFile(const std::string& filename, GLenum shaderType);
  uint32_t m_shader { 0 }; //shader object id
};

#endif // __SHADER_H__