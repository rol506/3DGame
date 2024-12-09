#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

enum EMoveDirection
{
  FORWARD, BACKWARD, LEFT, RIGHT
};

namespace RenderEngine
{
  class Camera
  {
  public:
    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.f, float pitch = 0.0f);
    ~Camera();

    glm::mat4 getViewMatrix();

    void processKeyboard(EMoveDirection direction, double delta);
    void processMouse(double xoffset, double yoffset, bool constrainPitch = true);

    void setPosition(glm::vec3 position);

  private:

    void updateCameraVectors();

    float m_yaw;
    float m_pitch;

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;
    glm::vec3 m_worldUp;

    float m_speed = 0.5f;
    float m_sensitivity = 0.1f;

  };
}
