#pragma once

#include "IGameState.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Renderer/Sprite.h"
#include <memory>
#include <string>

#include "../../Renderer/Camera.h"

class GameStateTest : public IGameState
{
public:

  GameStateTest();
  ~GameStateTest();

  void render() const;
  void update(const double deltaTime);
  void processInput(std::array<bool, 349> keys);
  void processMouseInput(double xoffset, double yoffset);
  void setFramebufferSize(int width, int height);

  unsigned int getStateWidth() const {return m_framebufferWidth;}
  unsigned int getStateHeight() const {return m_framebufferHeight;}

private:

  int m_framebufferWidth;
  int m_framebufferHeight;

  std::shared_ptr<RenderEngine::ShaderProgram> m_shader;
  std::shared_ptr<RenderEngine::Sprite>        m_sprite;

  std::array<bool, 349> m_keys;
  std::array<bool, 349> m_keysOld;
  std::array<std::string, 6> m_blockSubTexNames;

  int m_currentSubTexIndex;

  std::shared_ptr<RenderEngine::Camera> m_camera;

};
