#pragma once

#include "IGameObject.h"

#include <glm/vec3.hpp>

#include "../../Renderer/ShaderProgram.h"
#include "../../Renderer/Texture2D.h"
#include "../../Renderer/VertexArray.h"
#include "../../Renderer/IndexBuffer.h"

#include <memory>

class Block : IGameObject
{
public:

  virtual void render() const = 0;

  virtual glm::vec3 getPosition() const = 0;
  virtual void setPosition(glm::vec3 position) = 0;

  virtual glm::vec3 getRotation() const {return glm::vec3(0.0f);}
  virtual void setRotation(glm::vec3 rotation) {};

protected:

  void init(std::shared_ptr<RenderEngine::Texture2D> texture);

  void renderMesh() const;

  RenderEngine::VertexArray m_vertexArray;
  RenderEngine::VertexBuffer m_vertexCoordsBuffer;
  RenderEngine::VertexBuffer m_textureCoordsBuffer;
  RenderEngine::IndexBuffer m_indexBuffer;

  std::shared_ptr<RenderEngine::ShaderProgram> m_shader;
  std::shared_ptr<RenderEngine::Texture2D> m_texture;

  glm::vec3 m_position;

};
