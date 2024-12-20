#pragma once

#include <glad/glad.h>
#include <string>

#include <glm/mat4x4.hpp>

namespace RenderEngine
{
  class ShaderProgram
  {
  public:

    ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram& operator=(ShaderProgram&& shader) noexcept;
    ShaderProgram(ShaderProgram&& shader) noexcept;

    void use() const;
    bool isCompiled() const {return m_isCompiled;}

    void setInt(const int value, const std::string& name);
    void setFloat(const float value, const std::string& name);
    void setMat4(const glm::mat4& matrix, const std::string& name);

  private:

    bool createShader(GLuint& shaderID, const std::string& shaderSource, const GLenum& shaderType);

    GLuint m_ID;
    bool m_isCompiled = false;

  };
}
