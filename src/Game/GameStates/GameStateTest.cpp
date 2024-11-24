#include "GameStateTest.h"

#include "../../Resources/ResourceManager.h"
#include "glm/ext/matrix_transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

GameStateTest::GameStateTest(): m_viewMatrix(1.0f), m_framebufferWidth(0), m_framebufferHeight(0)
{
  m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
  m_shader = ResourceManager::getShaderProgram("SpriteShader");
  m_sprite = ResourceManager::loadSprite("GRASSBLOCK", "SpriteShader", "GRASS", "FRONT");
  
  m_shader->use();
  m_shader->setMat4(m_viewMatrix, "viewMatrix");
  std::cout << "Game state initialized!\n";
}

GameStateTest::~GameStateTest()
{
  std::cout << "Game state destroyed!\n";
}

void GameStateTest::render() const
{ 
  m_sprite->render(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)); 
}

void GameStateTest::update(const double deltaTime)
{
  //process input
  if (m_keys[GLFW_KEY_W])
  {
    m_shader->use();
    m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, -0.2f, 0.0f) * static_cast<float>(deltaTime));
    m_shader->setMat4(m_viewMatrix, "viewMatrix");
  }
  if (m_keys[GLFW_KEY_S])
  {
    m_shader->use();
    m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f,  0.2f, 0.0f) * static_cast<float>(deltaTime));
    m_shader->setMat4(m_viewMatrix, "viewMatrix");
  }
  if (m_keys[GLFW_KEY_A])
  {
    m_shader->use();
    m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3( 0.2f, 0.0f, 0.0f) * static_cast<float>(deltaTime));
    m_shader->setMat4(m_viewMatrix, "viewMatrix");
  }
  if (m_keys[GLFW_KEY_D])
  {
    m_shader->use();
    m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(-0.2f, 0.0f, 0.0f) * static_cast<float>(deltaTime));
    m_shader->setMat4(m_viewMatrix, "viewMatrix");
  }
  if (m_keys[GLFW_KEY_Z])
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
  }
}

void GameStateTest::processInput(std::array<bool, 349> keys)
{
  m_keys = keys;
}

void GameStateTest::setFramebufferSize(int width, int height)
{
  m_framebufferWidth = width;
  m_framebufferHeight = height;
}
