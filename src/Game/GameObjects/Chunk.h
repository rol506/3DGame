#pragma once

#include "Block.h"

#include <glm/vec3.hpp>

#include <unordered_map>
#include <memory>

const int CHUNK_WIDTH = 16;
const int CHUNK_HEIGHT = 16;

class Chunk
{
public:
  
  Chunk(const glm::vec3 chunkPos);
  ~Chunk();

  void render() const;

  //returns nullptr if the block is air
  const std::shared_ptr<Block> getBlock(const int X, const int Y, const int Z) const;

  void setBlock(std::shared_ptr<Block> block);
  void removeBlock(const glm::vec3 positionChunk);

private:
  
  //MEMORY LAYOUT
  //in this list first el (aka 0) is the block on (0, 0, 0) position
  //then we go z++, then x++, then y++
  //(first we do 1 row then another row, after 16 rows we climb up 1 Y pos)
  //so I can caclulate block position to get the block data
  //
  //MATH
  //to access block on pos (X, Y, Z):
  //first calc POS = Y * CHUNK_WIDTH * CHUNK_HEIGHT
  //then POS += X * CHUNK_WIDTH
  //then POS += Z
  //
  //so POS is the index of the block
  //
  //POSITION IN CHUNK COORDINATES!!!

  std::unordered_map<long long, std::shared_ptr<Block>> m_blocks = {};

  glm::vec3 m_position; //chunk coord position

};
