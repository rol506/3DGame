#pragma once

#include <array>
#include <string>

enum EBlockType
{
  GRASS = 0,
  GRASS_DEBUG = 1
};

struct BlockType {
  std::string textureName;
};

const std::array<BlockType, 2> BlockTypes = {
  //GRASS
  BlockType{"GRASS"},
  BlockType{"GRASS_DEBUG"}
};
