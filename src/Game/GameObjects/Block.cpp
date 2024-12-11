#include "Block.h"

#include "../../Resources/ResourceManager.h"

#include "../../Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

void Block::init(std::shared_ptr<RenderEngine::Texture2D> texture)
{
  m_shader = ResourceManager::getShaderProgram("SpriteShader");
  m_texture = texture;

  m_shader = ResourceManager::getShaderProgram("SpriteShader");
  m_texture = ResourceManager::getTexture("GRASS");

  auto& front  = m_texture->getSubTexture("FRONT");
  auto& left   = m_texture->getSubTexture("LEFT");
  auto& back   = m_texture->getSubTexture("BACK");
  auto& right  = m_texture->getSubTexture("RIGHT");
  auto& bottom = m_texture->getSubTexture("BOTTOM");
  auto& top    = m_texture->getSubTexture("TOP");

  GLfloat vertices[] = {
    // 1 - 2
    // | / |
    // 0 - 3

    //X      Y     Z              U                     V

    //front
    -0.5f, -0.5f,  0.5f, front.leftBottomUV.x,  front.leftBottomUV.y, //0
    -0.5f,  0.5f,  0.5f, front.leftBottomUV.x,  front.rightTopUV.y,   //1
     0.5f,  0.5f,  0.5f, front.rightTopUV.x,    front.rightTopUV.y,   //2
     0.5f, -0.5f,  0.5f, front.rightTopUV.x,    front.leftBottomUV.y, //3

    //left
    -0.5f, -0.5f, -0.5f, left.leftBottomUV.x,   left.leftBottomUV.y,   //4
    -0.5f,  0.5f, -0.5f, left.leftBottomUV.x,   left.rightTopUV.y,     //5
    -0.5f,  0.5f,  0.5f, left.rightTopUV.x,     left.rightTopUV.y,     //6 - 1
    -0.5f, -0.5f,  0.5f, left.rightTopUV.x,     left.leftBottomUV.y,   //7 - 0
    
    //back
     0.5f, -0.5f, -0.5f, back.leftBottomUV.x,   back.leftBottomUV.y,   //8
     0.5f,  0.5f, -0.5f, back.leftBottomUV.x,   back.rightTopUV.y,     //9
    -0.5f,  0.5f, -0.5f, back.rightTopUV.x,     back.rightTopUV.y,     //10 - 5
    -0.5f, -0.5f, -0.5f, back.rightTopUV.x,     back.leftBottomUV.y,    //11 - 4

    //right
     0.5f, -0.5f,  0.5f, right.leftBottomUV.x,  right.leftBottomUV.y,  //12 - 3
     0.5f,  0.5f,  0.5f, right.leftBottomUV.x,  right.rightTopUV.y,    //13 - 2
     0.5f,  0.5f, -0.5f, right.rightTopUV.x,    right.rightTopUV.y,    //14 - 9
     0.5f, -0.5f, -0.5f, right.rightTopUV.x,    right.leftBottomUV.y,  //15 - 8
    
    //bottom
    -0.5f, -0.5f,  0.5f, bottom.leftBottomUV.x, bottom.leftBottomUV.y, //16 - 0
    -0.5f, -0.5f, -0.5f, bottom.leftBottomUV.x, bottom.rightTopUV.y,   //17 - 4
     0.5f, -0.5f, -0.5f, bottom.rightTopUV.x,   bottom.rightTopUV.y,   //18 - 8
     0.5f, -0.5f,  0.5f, bottom.rightTopUV.x,   bottom.leftBottomUV.y,  //19 - 3

     //top
    -0.5f,  0.5f,  0.5f, top.leftBottomUV.x,    top.leftBottomUV.y,    //20 - 1
    -0.5f,  0.5f, -0.5f, top.leftBottomUV.x,    top.rightTopUV.y,      //21 - 5
     0.5f,  0.5f, -0.5f, top.rightTopUV.x,      top.rightTopUV.y,      //22 - 9
     0.5f,  0.5f,  0.5f, top.rightTopUV.x,      top.leftBottomUV.y,    //23 - 2
  };

  GLuint indices[] = {
    /*0, 1, 2,
    0, 2, 3,

    4, 5, 1,
    4, 1, 0,

    8, 9, 10,
    8, 10, 4,

    3, 2, 9,
    3, 9, 8,

    0, 4, 8,
    0, 8, 3,

    1, 5, 9,
    1, 9, 2*/
 
    0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    8, 9, 10,
    8, 10, 11,

    12, 13, 14,
    12, 14, 15,

    16, 17, 18,
    16, 18, 19,

    20, 21, 22,
    20, 22, 23
  };

  RenderEngine::VertexBufferLayout vertexCoordsLayout;
  vertexCoordsLayout.reserve(1);
  vertexCoordsLayout.addElementLayoutFloat(3, false);
  vertexCoordsLayout.addElementLayoutFloat(2, false);

  m_vertexCoordsBuffer.init(vertices, sizeof(vertices));

  m_indexBuffer.init(indices, 36);

  m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

  m_vertexArray.unbind();
  m_vertexCoordsBuffer.unbind(); 
}

void Block::renderMesh() const
{
  m_shader->use();

  glm::mat4 model(1.0f);
  model = glm::translate(model, m_position);

  m_shader->setInt(0, "tex");
  glActiveTexture(GL_TEXTURE0);

  m_texture->bind();

  m_shader->setMat4(model, "modelMatrix");

  RenderEngine::Renderer::draw(m_vertexArray, m_indexBuffer, *m_shader);
}

