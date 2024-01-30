#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) {
  auto shader = std::unique_ptr<Shader>(new Shader());
  if (!shader->LoadFile(filename, shaderType))
    return nullptr;
  return std::move(shader); // shader memory move to out of inner class
}

Shader::~Shader() {
  if (m_shader) {
    glDeleteShader(m_shader);
  }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) {
    auto result = LoadTextFile(filename); // in common.h
    if (!result.has_value())
        return false;

    auto& code = result.value();
    const char* codePtr = code.c_str(); //c_str() is to get a pointer of string 
    int32_t codeLength = (int32_t)code.length();

    // create and compile shader
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shader); //compile to source code of shader

    int success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);//get a shader information in format compile status ex) failure
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog); //get the error message info.
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    
    return true;


}