#pragma once

#include <glm/vec3.hpp>

#include "../../Renderer/ShaderProgram.h"
#include "../../Renderer/Texture2D.h"
#include "../../Renderer/VertexArray.h"
#include "../../Renderer/IndexBuffer.h"

#include "BlockTypes.h"

#include <memory>

class Block
{
public:

  Block(EBlockType blockType, const glm::ivec3 position = glm::vec3(0.0f));
  ~Block();

  Block(const Block& block) = delete;
  Block& operator=(const Block& block) = delete;
  Block& operator=(Block&& block) noexcept;
  Block(Block&& block) noexcept;

  void render(const glm::vec3 chunkPosition = glm::vec3(0.0f)) const;

  void setPosition(const glm::ivec3 position);
  const glm::ivec3 getPosition() const;

private:

  void init(std::shared_ptr<RenderEngine::Texture2D> texture);

  void renderMesh(const glm::vec3 chunkPosition) const;

  RenderEngine::VertexArray m_vertexArray;
  RenderEngine::VertexBuffer m_vertexCoordsBuffer;
  RenderEngine::VertexBuffer m_textureCoordsBuffer;
  RenderEngine::IndexBuffer m_indexBuffer;

  std::shared_ptr<RenderEngine::ShaderProgram> m_shader;
  std::shared_ptr<RenderEngine::Texture2D> m_texture;

  glm::ivec3 m_position;
};
