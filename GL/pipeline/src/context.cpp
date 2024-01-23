#include "context.h"
#include <iostream>

ContextUPtr Context::Create()
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init()
{
    // vertex data
    //  float vertices[] = {
    //      -0.5f, -0.5f, 0.0f,
    //      0.5f, -0.5f, 0.0f,
    //      0.0f, 0.5f, 0.0f,
    //  };

    //     float vertices[] = {
    //     // first triangle
    //     0.5f, 0.5f, 0.0f, // top right
    //     0.5f, -0.5f, 0.0f, // bottom right
    //     -0.5f, 0.5f, 0.0f, // top left
    //     // second triangle
    //     0.5f, -0.5f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f // top left
    //   };

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  // top left
    };
    uint32_t indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    // VAO
    // glGenVertexArrays(1, &m_vertexArrayObject);
    // glBindVertexArray(m_vertexArrayObject);
    //=
    m_vertexLayout = VertexLayout::Create();

    // VBO vertex
    // glGenBuffers(1, &m_vertexBuffer);              // create vertex buffer
    // glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // GL_ARRAY_BUFFER = VBO
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);
    //=
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW,vertices, sizeof(float) * 12);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    //=
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    

    // VBO index
    // glGenBuffers(1, &m_indexBuffer);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indices, GL_STATIC_DRAW);
    //=
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW,indices, sizeof(uint32_t) * 6);
    
    /*
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float)*3, 0);
    those code is not required
    */

    glBindVertexArray(0); // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader)
    {
        return false;
    }

    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});

    if (!m_program)
    {
        return false;
    }

    SPDLOG_INFO("program id: {}", m_program->Get());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // temp vertex array object
    //  uint32_t vao = 0;
    //  glGenVertexArrays(1, &vao);
    //  glBindVertexArray(vao);
    return true;
}

void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glUseProgram(m_program->Get());
    m_program->Use();
    glBindVertexArray(m_vertexLayout->Get());
    //  glDrawArrays(GL_POINTS, 0, 1); //func of drawing a red point.
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawArrays(GL_LINE_STRIP, 0, 4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glFlush();
}