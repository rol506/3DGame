#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>

namespace RenderEngine
{
    
  Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
  {
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
  }

  Camera::~Camera()
  {
  }

  void Camera::setPosition(glm::vec3 position)
  {
    m_position = position;
  }

  glm::mat4 Camera::getViewMatrix()
  {
    return glm::lookAt(m_position, m_position + m_front, m_up);
  }

  void Camera::updateCameraVectors()
  {
    glm::vec3 front;
    /*
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));*/
    front = glm::vec3(cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)), sin(glm::radians(m_pitch)), sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
  }

  void Camera::processKeyboard(EMoveDirection direction, double delta)
  {
    float velocity = m_speed * delta;
    if (direction == EMoveDirection::FORWARD)
      m_position += m_front * velocity;
    if (direction == EMoveDirection::BACKWARD)
      m_position -= m_front * velocity;
    if (direction == EMoveDirection::LEFT)
      m_position -= glm::normalize(m_right) * velocity;
    if (direction == EMoveDirection::RIGHT)
      m_position += glm::normalize(m_right) * velocity;
  }

  void Camera::processMouse(double xoffset, double yoffset, bool constrainPitch)
  {
    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch)
    {
      if (m_pitch > 89.0f)
        m_pitch = 89.0f;
      else if (m_pitch < -89.0f)
        m_pitch = -89.0f;

      if (m_yaw > 360.f)
        m_yaw = 0;
      else if (m_yaw < 0.0f)
        m_yaw = 360.f;
    }

    std::cout << "yaw: " << m_yaw << " pitch: " << m_pitch << std::endl;

    updateCameraVectors();
  }

}
