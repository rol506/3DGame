#pragma once

#include <glad/glad.h>

namespace RenderEngine
{
  class IndexBuffer
  {
  public:

    IndexBuffer();
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&& buffer) noexcept;
    IndexBuffer(IndexBuffer&& buffer) noexcept;

    void bind() const;
    void unbind() const;
    void init(const void* data, const unsigned int count);
    unsigned int getCount() const {return m_count;};

  private:

    GLuint m_ID;
    unsigned int m_count;

  };
}
