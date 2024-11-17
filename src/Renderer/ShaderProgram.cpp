#include "ShaderProgram.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

namespace RenderEngine
{
  bool ShaderProgram::createShader(GLuint& shaderID, const std::string& shaderSource, const GLenum& shaderType)
  {
    shaderID = glCreateShader(shaderType);
    const char* code = shaderSource.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      GLchar infoLog[1024];
      glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
      std::cerr << "Failed to create shader: " <<  infoLog << "\n";
      return false;
    }
    return true;
  }

  ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
  {
    GLuint vertexID;
    if (!createShader(vertexID, vertexSource, GL_VERTEX_SHADER))
    {
      std::cerr << "Failed to create vertex shader!\n";
      return;
    }

    GLuint fragmentID;
    if (!createShader(fragmentID, fragmentSource, GL_FRAGMENT_SHADER))
    {
      glDeleteShader(vertexID);
      std::cerr << "Failed to create fragment shader!\n";
      return;
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexID);
    glAttachShader(m_ID, fragmentID);
    glLinkProgram(m_ID);

    GLint success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
      GLchar infoLog[1024];
      glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
      std::cerr << "Failed to create shader program: " << infoLog << "\n";
      m_isCompiled = false;
    } else {
      m_isCompiled = true;
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
  }

  void ShaderProgram::use() const
  {
    glUseProgram(m_ID);
  }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shader) noexcept
    {
      if (this != &shader)
      {
        glDeleteProgram(m_ID);

        m_ID = shader.m_ID;
        m_isCompiled = shader.m_isCompiled;

        shader.m_ID = 0;
        shader.m_isCompiled = false;
      }
      return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shader) noexcept
    {
      m_ID = shader.m_ID;
      m_isCompiled = shader.m_isCompiled;

      shader.m_ID = 0;
      shader.m_isCompiled = false;
    }

    ShaderProgram::~ShaderProgram()
    {
      glDeleteProgram(m_ID);
    }

    void ShaderProgram::setInt(const int value, const std::string& name)
    {
      glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

  void ShaderProgram::setFloat(const float value, const std::string& name)
  {
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
  }

  void ShaderProgram::setMat4(const glm::mat4& matrix, const std::string& name)
  {
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
  }
}
