#include "VertexBufferLayout.h"

namespace RenderEngine 
{
  VertexBufferLayout::VertexBufferLayout() : m_stride(0)
  {}

  void VertexBufferLayout::reserve(const size_t count)
  {
    m_layoutElements.reserve(count);
  }

  void VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
  {
    m_layoutElements.push_back({count, GL_FLOAT, normalized, count * static_cast<unsigned int>(sizeof(GLfloat))}); 
    m_stride += m_layoutElements.back().size;
  }

  VertexBufferLayout::~VertexBufferLayout()
  {
    m_layoutElements.clear();
    m_stride = 0;
  }
}
