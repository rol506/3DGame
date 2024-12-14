#include "Game.h"

#include "../Renderer/Renderer.h"
#include "../Resources/ResourceManager.h"
#include "GLFW/glfw3.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>
#include <iostream>

Game::Game(GLFWwindow* windowptr): m_projectionMatrix(1.0f), m_framebufferSize(0.f), m_window(windowptr)
{
  m_keys.fill(false);

  //load resources for other classes to use
  m_spriteShader = ResourceManager::loadShaders("SpriteShader", "res/shaders/vSprite.vert", "res/shaders/fSprite.frag"); 
  std::vector<std::string> blockSubTextures = {"FRONT", "LEFT", "BACK", "RIGHT", "BOTTOM", "TOP"};

  //load textures
  ResourceManager::loadTextureAtlas("GRASS", "res/textures/grass16x16.jpg", 16, 16, blockSubTextures);
  ResourceManager::loadTextureAtlas("GRASS_DEBUG", "res/textures/grass16x16debug.jpg", 16, 16, blockSubTextures);

  m_spriteShader->use();
  m_spriteShader->setMat4(m_projectionMatrix, "projectionMatrix");

  std::cout << "Game initialized!\n";
}

Game::~Game()
{
  std::cout << "Game destroyed!\n";
}

void Game::update(double deltaTime)
{
  m_gameState->update(deltaTime);
  m_gameState->render();
}

void Game::setFramebufferSize(int width, int height)
{
  m_framebufferSize = glm::ivec2(width, height);
  RenderEngine::Renderer::setViewport(width, height);
  m_projectionMatrix = glm::perspective(glm::radians(60.0f), static_cast<float>(width)/static_cast<float>(height), 0.1f, 100.f);
  m_gameState->setFramebufferSize(width, height);
  m_spriteShader->use();
  m_spriteShader->setMat4(m_projectionMatrix, "projectionMatrix");
}

void Game::setKey(const int key, const int action)
{
  m_keys[key] = action;
  m_gameState->processInput(m_keys);
}

void Game::setMouse(const double xoffset, const double yoffset)
{
  m_gameState->processMouseInput(xoffset, yoffset);
}

void Game::setGameState(std::shared_ptr<IGameState> gameStatePtr)
{
  m_gameState = gameStatePtr;
}
