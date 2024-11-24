#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture2D.h"
#include "ShaderProgram.h"

#include <memory>
#include <string>

#include <glm/vec3.hpp>

namespace RenderEngine
{
  class Sprite
  {
  public:

    Sprite(std::shared_ptr<RenderEngine::Texture2D> texture, const std::string& initialSubTexture, std::shared_ptr<RenderEngine::ShaderProgram> shaderProgram);
    ~Sprite();

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;
    Sprite& operator=(Sprite&& sprite) noexcept;
    Sprite(Sprite&& sprite) noexcept;

    void render(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation);
    void setSubTexture(const std::string& subTexture);
    void setSubTexture(std::shared_ptr<Texture2D> texture, const std::string& subTexture);

  private:

    std::shared_ptr<RenderEngine::ShaderProgram> m_shaderProgram;
    std::shared_ptr<RenderEngine::Texture2D> m_texture;

    VertexBuffer m_vertexBuffer;
    VertexArray m_vertexArray;
    IndexBuffer m_indexBuffer;

  };
}
