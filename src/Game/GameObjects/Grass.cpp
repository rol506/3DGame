#include "Grass.h"

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Resources/ResourceManager.h"

Grass::Grass(glm::vec3 position)
{
  std::shared_ptr<RenderEngine::Texture2D> texture = ResourceManager::getTexture("GRASS");
  init(texture);
  setPosition(position);
}

Grass::~Grass()
{
}
  
void Grass::setPosition(glm::vec3 position)
{
  m_position = position;
}

glm::vec3 Grass::getPosition() const
{
  return m_position;
}

void Grass::render() const
{
  renderMesh(); 
}

