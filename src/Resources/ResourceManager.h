#pragma once

#include <memory>
#include <map>
#include <string>

namespace RenderEngine
{
  class ShaderProgram;
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

private:

  static std::string getFileString(const std::string& relativeFilePath);

  static std::string m_path;

  typedef std::map<std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
  static ShaderProgramsMap m_shaderPrograms;

};
