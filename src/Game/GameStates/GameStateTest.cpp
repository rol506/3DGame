#include "GameStateTest.h"

#include "../../Resources/ResourceManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

GameStateTest::GameStateTest(): m_framebufferWidth(0), m_framebufferHeight(0), m_currentSubTexIndex(0)
{
  m_keys.fill(false);
  m_keysOld.fill(false);
  
  m_camera = std::make_shared<RenderEngine::Camera>(glm::vec3(0.0f));
  m_camera->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

  m_shader = ResourceManager::getShaderProgram("SpriteShader"); 
  
  m_blockSubTexNames = {"FRONT", "LEFT", "BACK", "RIGHT", "BOTTOM", "TOP"};

  m_shader->use();
  m_shader->setMat4(m_camera->getViewMatrix(), "viewMatrix");

  m_chunk = std::make_shared<Chunk>(glm::vec3(0.0f));

  //generate world

  int X = 0, Y = 0, Z = 0;

  for (int i=0;i<16*16;++i)
  {
    if (X>CHUNK_WIDTH-1)
    {
      X = 0;
      Z += 1;
    }

    if (Z>CHUNK_WIDTH-1)
    {
      Z = 0;
      Y += 1;
    }

    glm::vec3 pos(X, Y, Z);
    ++X;

    m_chunk->setBlock(std::make_shared<Block>(EBlockType::GRASS, pos));
  }

  m_chunk->removeBlock(glm::vec3(0.0f));

  std::cout << "Game state initialized!\n";
}

GameStateTest::~GameStateTest()
{
  std::cout << "Game state destroyed!\n";
}

void GameStateTest::render() const
{ 
  m_shader->setMat4(m_camera->getViewMatrix(), "viewMatrix");
  m_chunk->render();
}

void GameStateTest::update(const double deltaTime)
{
  //process input
  if (m_keys[GLFW_KEY_W])
  {
    m_shader->use();
    //m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, -0.2f, 0.0f) * static_cast<float>(deltaTime));
    m_camera->processKeyboard(EMoveDirection::FORWARD, deltaTime);
  }
  if (m_keys[GLFW_KEY_S])
  {
    m_shader->use();
    //m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f,  0.2f, 0.0f) * static_cast<float>(deltaTime));
    m_camera->processKeyboard(EMoveDirection::BACKWARD, deltaTime);
  }
  if (m_keys[GLFW_KEY_A])
  {
    m_shader->use();
    //m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3( 0.2f, 0.0f, 0.0f) * static_cast<float>(deltaTime));
    m_camera->processKeyboard(EMoveDirection::LEFT, deltaTime);
  }
  if (m_keys[GLFW_KEY_D])
  {
    m_shader->use();
    //m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(-0.2f, 0.0f, 0.0f) * static_cast<float>(deltaTime));
    m_camera->processKeyboard(EMoveDirection::RIGHT, deltaTime);
  }
  /*if (m_keys[GLFW_KEY_Z])
  {
    m_shader->use();
    m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, 0.0f, -0.2f) * static_cast<float>(deltaTime));
    m_shader->setMat4(m_viewMatrix, "viewMatrix");
  }
  if (m_keys[GLFW_KEY_X])
  {
    m_shader->use();
    m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, 0.0f,  0.2f) * static_cast<float>(deltaTime));
    m_shader->setMat4(m_viewMatrix, "viewMatrix");
  }*/

  /*if (m_keysOld[GLFW_KEY_KP_ADD] && !m_keys[GLFW_KEY_KP_ADD])
  {
    m_currentSubTexIndex++;
    if (m_currentSubTexIndex > m_blockSubTexNames.size()-1)
      m_currentSubTexIndex = 0;
    m_sprite->setSubTexture(m_blockSubTexNames[m_currentSubTexIndex]);

    //clear old
    m_keysOld[GLFW_KEY_KP_ADD] = 0;
  }
  
  if (m_keysOld[GLFW_KEY_KP_SUBTRACT] && !m_keys[GLFW_KEY_KP_SUBTRACT])
  {
    m_currentSubTexIndex--;
    if (m_currentSubTexIndex < 0)
      m_currentSubTexIndex = m_blockSubTexNames.size()-1;
    m_sprite->setSubTexture(m_blockSubTexNames[m_currentSubTexIndex]);

    //clear old
    m_keysOld[GLFW_KEY_KP_SUBTRACT] = 0;
  }*/
}

void GameStateTest::processInput(std::array<bool, 349> keys)
{
  m_keysOld = m_keys;
  m_keys = keys;
}

void GameStateTest::processMouseInput(double xoffset, double yoffset)
{
  m_camera->processMouse(xoffset, yoffset);
}

void GameStateTest::setFramebufferSize(int width, int height)
{
  m_framebufferWidth = width;
  m_framebufferHeight = height;
}
