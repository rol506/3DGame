#pragma once

#include <glad/glad.h>

namespace RenderEngine
{
  class Texture2D
  {
  public:

    Texture2D(const unsigned int width, const unsigned int height, const unsigned int channels, const unsigned char* data,
              const GLenum filter, const GLenum wrapMode);

    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D& operator=(Texture2D&& texture);
    Texture2D(Texture2D&& texture);

    unsigned int getWidth() const {return m_width;}
    unsigned int getHeight() const {return m_height;}

    void bind() const;

  private:

    GLuint m_ID;
    GLenum m_mode;

    unsigned int m_width;
    unsigned int m_height;

  };
}
