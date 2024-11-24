#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

#include <glm/vec2.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

std::string ResourceManager::m_path;
ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
ResourceManager::TexturesMap ResourceManager::m_textures;
ResourceManager::SpritesMap ResourceManager::m_sprites;

void ResourceManager::setExecutablePath(const std::string& path)
{
  std::size_t found = path.find_last_of("/\\");
  m_path = path.substr(0, found);
}

void ResourceManager::unloadAllResources()
{
  m_shaderPrograms.clear();
  m_textures.clear();
  m_sprites.clear();
  m_path.clear();
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath)
{
  std::ifstream f;
  f.open(m_path + "/" + relativeFilePath, std::ios::in | std::ios::binary);
  if (!f.is_open())
  {
    std::cerr << "Failed to open file: " << relativeFilePath << "\n";
    return std::string{};
  }

  std::stringstream buf;
  buf << f.rdbuf();
  return buf.str();
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
  std::string vertexSource = getFileString(vertexPath);
  if (vertexSource.empty())
  {
    std::cout << "No vertex shader!\n";
    return nullptr;
  }

  std::string fragmentSource = getFileString(fragmentPath);
  if (fragmentSource.empty())
  {
    std::cout << "No fragment shader!\n";
    return nullptr;
  }

  std::shared_ptr<RenderEngine::ShaderProgram> newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgram>(vertexSource, fragmentSource)).first->second;
  if (newShader->isCompiled())
  {
    return newShader;
  }

  std::cerr << "Can't load the shader program: " << shaderName << "\n    Vertex: " << vertexPath << "\n    Fragment: " << fragmentPath << "\n";
  return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
  auto it = m_shaderPrograms.find(shaderName);
  if (it != m_shaderPrograms.end())
  {
    return it->second;
  }

  std::cout << "Can't find the shader program: " << shaderName << "\n";
  return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath,
                                                              const GLenum wrapMode, const GLenum filter)
{
  int width;
  int height;
  int channels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

  if (!data)
  {
    std::cerr << "Failed to load texture: " << texturePath << "\n";
    return nullptr;
  }

  std::shared_ptr<RenderEngine::Texture2D> newTexture = m_textures.emplace(textureName, std::make_shared<RenderEngine::Texture2D>(width, height, channels,
                                                                                                                                  data, filter, wrapMode)).first->second;

  stbi_image_free(data);
  return newTexture;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
  auto it = m_textures.find(textureName);
  if (it != m_textures.end())
  {
    return it->second;
  }

  std::cerr << "Can't find texture: " << textureName << "\n";
  return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(const std::string& textureName, const std::string& texturePath,
                                                                   const unsigned int width, const unsigned int height, const std::vector<std::string>& subTexturesNames,
                                                                   const GLenum wrapMode, const GLenum filter)
{
  auto texture = loadTexture(std::move(textureName), std::move(texturePath), wrapMode, filter);
  if (texture)
  {
    const unsigned int textureWidth = texture->getWidth();
    const unsigned int textureHeight = texture->getHeight();
    unsigned int currentTextureOffsetX = 0;
    unsigned int currentTextureOffsetY = textureHeight;
  
    for (auto& currentSubTextureName : subTexturesNames)
    {
      glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX)/textureWidth, static_cast<float>(currentTextureOffsetY - height)/textureHeight);
      glm::vec2 rightTopUV(  static_cast<float>(currentTextureOffsetX + width)/textureWidth, static_cast<float>(currentTextureOffsetY)/textureHeight);
      texture->addSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);

      currentTextureOffsetX += width;
      if (currentTextureOffsetX >= textureWidth)
      {
        currentTextureOffsetX = 0;
        currentTextureOffsetY -= height;
      }
    }

  }
  return texture;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprite(const std::string& spriteName, const std::string& shaderName, const std::string& textureName,
                                                          const std::string& subTextureName)
{
  auto shader = getShaderProgram(std::move(shaderName));
  if (!shader)
  {
    std::cout << "Can't find the shader program: " << shaderName << " for the sprite: " << spriteName << "\n";
    return nullptr;
  }

  auto texture = getTexture(std::move(textureName));
  if (!texture)
  {
    std::cout << "Can't find the texture: " << textureName << " for the sprite: " << spriteName << "\n";
    return nullptr;
  }

  std::shared_ptr<RenderEngine::Sprite> newSprite = m_sprites.emplace(spriteName, std::make_shared<RenderEngine::Sprite>(texture, subTextureName, shader)).first->second;

  return newSprite;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::getSprite(const std::string& spriteName)
{
  auto it = m_sprites.find(spriteName);
  if (it != m_sprites.end())
  {
    return it->second;
  }

  std::cout << "Can't find the sprite: " << spriteName << "\n";
  return nullptr;
}
