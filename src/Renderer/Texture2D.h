#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <map>
#include <string>

namespace RenderEngine
{
  class Texture2D
  {
  public:

    struct SubTexture2D
    {
      glm::vec2 leftBottomUV;
      glm::vec2 rightTopUV;

      SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV)
        : leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV) {}

      SubTexture2D() : leftBottomUV(0.f), rightTopUV(1.f) {}
    };

    Texture2D(const unsigned int width, const unsigned int height, const unsigned int channels, const unsigned char* data,
              const GLenum filter, const GLenum wrapMode);

    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D& operator=(Texture2D&& texture) noexcept;
    Texture2D(Texture2D&& texture) noexcept;

    unsigned int getWidth() const {return m_width;}
    unsigned int getHeight() const {return m_height;}

    void bind() const;

    void addSubTexture(const std::string& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
    const SubTexture2D getSubTexture(const std::string& name) const;

  private:

    GLuint m_ID;
    GLenum m_mode;

    unsigned int m_width;
    unsigned int m_height;

    std::map<std::string, SubTexture2D> m_subTextures;

  };
}
