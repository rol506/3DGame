#include "Chunk.h"
#include "BlockTypes.h"

Chunk::Chunk(const glm::vec3 chunkPos)
  : m_position(chunkPos)
{
  setBlock(std::make_shared<Block>(EBlockType::GRASS, glm::vec3(0.0f)));
}

Chunk::~Chunk()
{
  m_blocks.clear();
}

void Chunk::render() const
{
  for (const auto& el : m_blocks)
  {
    el.second->render();
  }
}

//returns nullptr if the block is air
const std::shared_ptr<Block> Chunk::getBlock(const int X, const int Y, const int Z) const
{
  const long long pos = (Y * CHUNK_WIDTH * CHUNK_HEIGHT) + (X * CHUNK_WIDTH) + Z;

  auto it = m_blocks.find(pos);
  if (it != m_blocks.end())
  {
    return it->second;
  }

  return nullptr;
}

void Chunk::setBlock(std::shared_ptr<Block> block)
{
  const glm::vec3 positionChunk = block->getPosition();
  const long long pos = (positionChunk.y * CHUNK_WIDTH * CHUNK_HEIGHT) + (positionChunk.x * CHUNK_WIDTH) + positionChunk.z; 
  //m_blocks.insert(std::next(m_blocks.begin(), pos), block);
  m_blocks.insert({pos, block});
}

void Chunk::removeBlock(const glm::vec3 positionChunk)
{
  const long long pos = (positionChunk.y * CHUNK_WIDTH * CHUNK_HEIGHT) + (positionChunk.x * CHUNK_WIDTH) + positionChunk.z; 
  auto it = m_blocks.find(pos);
  if (it != m_blocks.end())
  {
    m_blocks.erase(it);
  }
}

