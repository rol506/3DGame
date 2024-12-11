#pragma once

#include "Block.h"

class Grass : Block
{
public:

  Grass(glm::vec3 position);
  ~Grass();
  
  void setPosition(glm::vec3 position) override;
  glm::vec3 getPosition() const override;

  void render() const override;

private:

};
