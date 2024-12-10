#pragma once

#include <glm/vec3.hpp>

class IGameObject {
public:

  virtual void setPosition(glm::vec3 position) = 0;
  virtual glm::vec3 getPosition() const = 0;
  virtual void setRotation(glm::vec3 rotation) = 0;
  virtual glm::vec3 getRotation() const = 0;

  virtual void render() const = 0;

protected:

  glm::vec3 m_position;
  glm::vec3 m_rotation;

};
