#include "VertexArray.h"

namespace RenderEngine
{
  VertexArray::VertexArray()
  {
    glGenVertexArrays(1, &m_ID);
  }

  VertexArray::~VertexArray()
  {
    glDeleteVertexArrays(1, &m_ID);
  }

  VertexArray& VertexArray::operator=(VertexArray&& array) noexcept
  {
    if (this != &array)
    {
      m_ID = array.m_ID;
      m_elementsCount = array.m_elementsCount;

      array.m_ID = 0;
      array.m_elementsCount = 0;
    }
    return *this;
  }

  VertexArray::VertexArray(VertexArray&& array) noexcept
  {
    m_ID = array.m_ID;
    m_elementsCount = array.m_elementsCount;

    array.m_ID = 0;
    array.m_elementsCount = 0;
  }

  void VertexArray::bind() const
  {
    glBindVertexArray(m_ID);
  }

  void VertexArray::unbind() const
  {
    glBindVertexArray(0);
  }

  void VertexArray::addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout)
  {
    glBindVertexArray(m_ID);
    buffer.bind();
    const auto& elements = layout.getLayoutElements();
    GLbyte* offset = nullptr;
    for (unsigned int i=0;i<elements.size();++i)
    {
      const auto& currentLayoutElement = elements[i];
      GLuint currentAttribIndex = m_elementsCount + i;
      glEnableVertexAttribArray(currentAttribIndex);
      glVertexAttribPointer(currentAttribIndex, currentLayoutElement.size, currentLayoutElement.type, 
          currentLayoutElement.normalized, layout.getStride(), offset);
      offset += currentLayoutElement.size;
    }
    m_elementsCount += static_cast<unsigned int>(elements.size());
  }


}
