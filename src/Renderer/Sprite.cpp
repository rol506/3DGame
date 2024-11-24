#include "Sprite.h"

#include "Renderer.h"
#include "glm/ext/matrix_transform.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RenderEngine
{
  Sprite::Sprite(std::shared_ptr<RenderEngine::Texture2D> texture, const std::string& initialSubTexture, std::shared_ptr<RenderEngine::ShaderProgram> shaderProgram)
    : m_texture(std::move(texture)), m_shaderProgram(std::move(shaderProgram))
  {

    auto subTexture = m_texture->getSubTexture(std::move(initialSubTexture));

    const GLfloat vertices[] = 
    {
      // 1 - 2
      // | / |
      // 0 - 3

      //X     Y     Z             U                          V
       0.0f,  0.0f, 0.0f, subTexture.leftBottomUV.x, subTexture.leftBottomUV.y, // 0
       0.0f,  1.0f, 0.0f, subTexture.leftBottomUV.x, subTexture.rightTopUV.y,    // 1
       1.0f,  1.0f, 0.0f, subTexture.rightTopUV.x,   subTexture.rightTopUV.y,    // 2
       1.0f,  0.0f, 0.0f, subTexture.rightTopUV.x,   subTexture.leftBottomUV.y   // 3
    };

    const GLuint indices[] = 
    {
      0, 1, 2,
      0, 2, 3
    };

    RenderEngine::VertexBufferLayout layout;
    layout.reserve(2);
    layout.addElementLayoutFloat(3, false);
    layout.addElementLayoutFloat(2, false);

    m_vertexBuffer.init(vertices, sizeof(vertices));
    
    m_vertexArray.addBuffer(m_vertexBuffer, layout);

    m_indexBuffer.init(indices, 6);

    m_vertexBuffer.unbind();
    m_vertexArray.unbind();
  }

  Sprite::~Sprite()
  {
  }

  Sprite& Sprite::operator=(Sprite&& sprite) noexcept
  {
    if (this != &sprite)
    {
      m_shaderProgram = std::move(sprite.m_shaderProgram);
      m_texture = std::move(sprite.m_texture);

      m_vertexBuffer = std::move(sprite.m_vertexBuffer);
      m_vertexArray = std::move(sprite.m_vertexArray);
      m_indexBuffer = std::move(sprite.m_indexBuffer);
    }
    return *this;
  }

  Sprite::Sprite(Sprite&& sprite) noexcept
  {
    m_shaderProgram = std::move(sprite.m_shaderProgram);
    m_texture = std::move(sprite.m_texture);

    m_vertexBuffer = std::move(sprite.m_vertexBuffer);
    m_vertexArray = std::move(sprite.m_vertexArray);
    m_indexBuffer = std::move(sprite.m_indexBuffer);
  }

  void Sprite::render(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation)
  {
    m_shaderProgram->use();

    m_shaderProgram->setInt(0, "tex");

    glActiveTexture(GL_TEXTURE0);
    m_texture->bind();
    
    glm::mat4 model(1.0f);
    /*model = glm::translate(model, position);
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));
    model = glm::scale(model, size);*/
    
    model = glm::translate(model, position);
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));
    model = glm::scale(model, size);

    m_shaderProgram->setMat4(model, "modelMatrix");

    Renderer::draw(m_vertexArray, m_indexBuffer, *m_shaderProgram);
  }

  void Sprite::setSubTexture(const std::string& subTexture)
  {
    auto subTex = m_texture->getSubTexture(std::move(subTexture));

    const GLfloat vertices[] = 
    {
      // 1 - 2
      // | / |
      // 0 - 3

      //X     Y     Z             U                          V
       0.0f,  0.0f, 0.0f, subTex.leftBottomUV.x, subTex.leftBottomUV.y,  // 0
       0.0f,  1.0f, 0.0f, subTex.leftBottomUV.x, subTex.rightTopUV.y,    // 1
       1.0f,  1.0f, 0.0f, subTex.rightTopUV.x,   subTex.rightTopUV.y,    // 2
       1.0f,  0.0f, 0.0f, subTex.rightTopUV.x,   subTex.leftBottomUV.y   // 3
    };

    const GLuint indices[] = 
    {
      0, 1, 2,
      0, 2, 3
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    RenderEngine::VertexBufferLayout layout;
    layout.reserve(2);
    layout.addElementLayoutFloat(3, false);
    layout.addElementLayoutFloat(2, false);

    vertexBuffer.init(vertices, sizeof(vertices));
    
    vertexArray.addBuffer(vertexBuffer, layout);

    indexBuffer.init(indices, 6);

    vertexBuffer.unbind();
    vertexArray.unbind();

    m_vertexArray = std::move(vertexArray);
    m_vertexBuffer = std::move(vertexBuffer);
    m_indexBuffer = std::move(indexBuffer);
  }

  void Sprite::setSubTexture(std::shared_ptr<Texture2D> texture, const std::string& subTexture)
  {
    m_texture = std::move(texture);
    auto subTex = m_texture->getSubTexture(std::move(subTexture));

    const GLfloat vertices[] = 
    {
      // 1 - 2
      // | / |
      // 0 - 3

      //X     Y     Z             U                          V
       0.0f,  0.0f, 0.0f, subTex.leftBottomUV.x, subTex.leftBottomUV.y,  // 0
       0.0f,  1.0f, 0.0f, subTex.leftBottomUV.x, subTex.rightTopUV.y,    // 1
       1.0f,  1.0f, 0.0f, subTex.rightTopUV.x,   subTex.rightTopUV.y,    // 2
       1.0f,  0.0f, 0.0f, subTex.rightTopUV.x,   subTex.leftBottomUV.y   // 3
    };

    const GLuint indices[] = 
    {
      0, 1, 2,
      0, 2, 3
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    RenderEngine::VertexBufferLayout layout;
    layout.reserve(2);
    layout.addElementLayoutFloat(3, false);
    layout.addElementLayoutFloat(2, false);

    vertexBuffer.init(vertices, sizeof(vertices));
    
    vertexArray.addBuffer(vertexBuffer, layout);

    indexBuffer.init(indices, 6);

    vertexBuffer.unbind();
    vertexArray.unbind();

    m_vertexArray = std::move(vertexArray);
    m_vertexBuffer = std::move(vertexBuffer);
    m_indexBuffer = std::move(indexBuffer);
  }

}
