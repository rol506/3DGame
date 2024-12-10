#pragma once

#include "IGameObject.h"

#include "../../Renderer/VertexArray.h"
#include "../../Renderer/VertexBuffer.h"
#include "../../Renderer/IndexBuffer.h"

#include "../../Renderer/Texture2D.h"
#include "../../Renderer/ShaderProgram.h"

#include <memory>

class Grass : IGameObject
{
public:

  Grass(glm::vec3 position);
  ~Grass();
  
  void setPosition(glm::vec3 position) override;
  glm::vec3 getPosition() const override;

  void setRotation(glm::vec3 rotation) override;
  glm::vec3 getRotation() const override;

  void render() const override;

private:

  std::shared_ptr<RenderEngine::ShaderProgram> m_shader;
  std::shared_ptr<RenderEngine::Texture2D> m_texture;

  RenderEngine::VertexArray m_vertexArray;
  RenderEngine::VertexBuffer m_vertexCoordsBuffer;
  RenderEngine::VertexBuffer m_textureCoordsBuffer;
  RenderEngine::IndexBuffer m_indexBuffer;

  glm::vec3 m_position;
  glm::vec3 m_rotation;

};
