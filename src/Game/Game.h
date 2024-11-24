#pragma once

#include <glad/glad.h>

#include "GameStates/IGameState.h"

#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

#include <array>

#include "../Renderer/ShaderProgram.h"
#include <memory>

class Game
{
public:

  Game(GLFWwindow* windowptr);
  ~Game();

  void update(double deltaTime);
  void setGameState(std::shared_ptr<IGameState> gameStatePtr);

  void setFramebufferSize(int width, int height);

  void setKey(const int key, const int action);

private:

  glm::mat4 m_projectionMatrix;

  glm::ivec2 m_framebufferSize;

  std::array<bool, 349> m_keys;
  
  GLFWwindow* m_window;

  std::shared_ptr<RenderEngine::ShaderProgram> m_spriteShader;

  std::shared_ptr<IGameState> m_gameState;
};
