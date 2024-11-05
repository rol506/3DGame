#pragma once

#include <memory>
#include <map>
#include <string>

#include <glad/glad.h>

namespace RenderEngine
{
  class ShaderProgram;
  class Texture2D;
}

class ResourceManager
{
public:
  ResourceManager() = delete;
  ~ResourceManager() = delete;

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  ResourceManager& operator=(ResourceManager&&) = delete;
  ResourceManager(ResourceManager&&) = delete;

  static void setExecutablePath(const std::string& path);
  static void unloadAllResources();

  static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
  static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);

  static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath,
                                                              const GLenum wrapMode=GL_CLAMP_TO_EDGE, const GLenum filter=GL_NEAREST);
  static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);

private:

  static std::string getFileString(const std::string& relativeFilePath);

  static std::string m_path;

  typedef std::map<std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
  static ShaderProgramsMap m_shaderPrograms;

  typedef std::map<std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
  static TexturesMap m_textures;

};
