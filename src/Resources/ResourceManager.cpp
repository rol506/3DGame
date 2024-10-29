#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "../Renderer/ShaderProgram.h"

std::string ResourceManager::m_path;
ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;

void ResourceManager::setExecutablePath(const std::string& path)
{
  std::size_t found = path.find_last_of("/\\");
  m_path = path.substr(0, found);
}

void ResourceManager::unloadAllResources()
{
  m_shaderPrograms.clear();
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
