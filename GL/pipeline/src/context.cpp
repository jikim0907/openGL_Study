#include "context.h"

ContextUPtr Context::Create() {
  auto context = ContextUPtr(new Context());
  if (!context->Init())
    return nullptr;
  return std::move(context);
}

bool Context::Init() {
  ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
  ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
  if (!vertShader || !fragShader){
    return false;
    }
  
  SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
  SPDLOG_INFO("fragment shader id: {}", fragShader->Get());
  
  m_program = Program::Create({fragShader, vertShader});
  
  if (!m_program){
    return false;
    }
  
  SPDLOG_INFO("program id: {}", m_program->Get());

  glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
  return true;
}