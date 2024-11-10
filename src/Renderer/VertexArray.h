#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>

namespace RenderEngine
{
  class VertexArray
  {
  public:
    
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&& array) noexcept;
    VertexArray(VertexArray&& array) noexcept;

    void bind() const;
    void unbind() const;
    void addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

  private:

    GLuint m_ID;
    unsigned int m_elementsCount;

  };
}
