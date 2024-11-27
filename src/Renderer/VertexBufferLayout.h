#pragma once

#include <vector>
#include <glad/glad.h>

namespace RenderEngine
{
  class VertexBufferLayout
  {
  public:

    struct VertexBufferLayoutElement
    {
      GLuint count;
      GLenum type;
      GLboolean normalized;
      unsigned int size;
    };

    VertexBufferLayout();
    ~VertexBufferLayout();

    void reserve(const size_t count);
    unsigned int getStride() const {return m_stride;}
    void addElementLayoutFloat(const unsigned int count, const bool normalized);
    const std::vector<VertexBufferLayoutElement> getLayoutElements() const {return m_layoutElements;}

  private:

    unsigned int m_stride;
    std::vector<VertexBufferLayoutElement> m_layoutElements;
  };
}
