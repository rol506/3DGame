#include "Texture2D.h"

namespace RenderEngine
{
  Texture2D::Texture2D(const unsigned int width, const unsigned int height, const unsigned int channels, const unsigned char* data,
              const GLenum filter, const GLenum wrapMode) : m_width(width), m_height(height)
  {
    switch(channels)
    {
      case 4:
        m_mode = GL_RGBA;
        break;
      case 3:
        m_mode = GL_RGB;
        break;
      default:
        m_mode = GL_RGBA;
        break;
    }

    glGenTextures(1, &m_ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);

    glGenerateMipmap(GL_TEXTURE_2D);
  }

  Texture2D::~Texture2D()
  {
    glDeleteTextures(1, &m_ID);
  }

  Texture2D& Texture2D::operator=(Texture2D&& texture)
  {
    if (this != &texture)
    {
      glDeleteTextures(1, &m_ID);
      m_ID = texture.m_ID;
      m_mode = texture.m_mode;
      m_width = texture.m_width;
      m_height = texture.m_height;

      texture.m_ID = 0;
      texture.m_width = 0;
      texture.m_height = 0;
    }
    return *this;
  }

  Texture2D::Texture2D(Texture2D&& texture)
  {
    m_ID = texture.m_ID;
    m_mode = texture.m_mode;
    m_width = texture.m_width;
    m_height = texture.m_height;

    texture.m_ID = 0;
    texture.m_width = 0;
    texture.m_height = 0;
  }

  void Texture2D::bind() const
  {
    glBindTexture(GL_TEXTURE_2D, m_ID);
  }
}
