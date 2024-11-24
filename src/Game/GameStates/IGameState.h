#pragma once

#include <array>

class IGameState
{
public:

  virtual ~IGameState() = default;

  virtual void render() const = 0;
  virtual void update(const double deltaTime) = 0;
  virtual void processInput(std::array<bool, 349> keys) = 0;
  virtual void setFramebufferSize(int width, int height) = 0;

  virtual unsigned int getStateWidth() const = 0;
  virtual unsigned int getStateHeight() const = 0;
};
