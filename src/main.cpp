#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cmath>
#include <chrono>

#include "Resources/ResourceManager.h"

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Renderer.h"
#include "Renderer/Sprite.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

glm::ivec2 gWindowSize(960, 540);

GLfloat vertices[] = {
  //X      Y     Z     R     G     B     U     V
  -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 0
  -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 1
   0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 2
   0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f  // 3
};

GLuint elements[] = {
  //  0 -- 3
  //  |  \ |
  //  1 -- 2
  0, 1, 2,
  0, 2, 3
};

void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "\n[OpenGL debug message] (" << id << "): " <<  message << "\n";

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << "\n";

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << "\n";
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << "\n";
    std::cout << "[OpenGL debug message]\n";
}

int main(int argc, char** argv)
{
  ResourceManager::setExecutablePath(argv[0]);
  std::cout << "Set executable path: " << argv[0] << "\n";

  if (!glfwInit())
  {
    std::cout << "glfwInit failed!\n";
    return 1;
  }
  
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWwindow* window = glfwCreateWindow(gWindowSize.x, gWindowSize.y, "3DGame by rol506", NULL, NULL);
  if (!window)
  {
    std::cout << "failed to create window!\n";
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGL())
  {
    std::cout << "Failed to load GLaD\n";
    glfwTerminate();
    return 1;
  }

  std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionStr() << "\n";
  std::cout << "OpenGL renderer: " << RenderEngine::Renderer::getRendererStr() << "\n";

  
  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
  {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    std::cout << "OpenGL debug context loaded!\n";
  }

  {
    
    std::vector<std::string> subTexturesNames = {"FRONT", "LEFT", "BACK", "RIGHT", "BOTTOM", "TOP"};
    auto shader = ResourceManager::loadShaders("DefaultShader", "res/shaders/vSprite.vert", "res/shaders/fSprite.frag");
    auto texture = ResourceManager::loadTextureAtlas("GRASS", "res/textures/grass16x16.jpg", 16, 16, subTexturesNames);
    auto sprite = ResourceManager::loadSprite("GrassBlock", "DefaultShader", "GRASS", "FRONT");

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(60.f), (float)gWindowSize.x/(float)gWindowSize.y, 0.1f, 100.f);

    glm::mat4 view(1.0f);
    glm::vec3 size(1.0f);
    glm::mat4 model(1.0f);

    model = glm::translate(model, glm::vec3(0.0f));
    model = glm::rotate(model, glm::radians(-55.f), glm::vec3(1.0f, 0.0f, 0.0f));

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    shader->use();
    shader->setMat4(projection, "projectionMatrix");

    glm::vec3 rotation(0.0f);

    //timing

    auto lastTime = std::chrono::high_resolution_clock::now();
    double deltaTime = 0;

    RenderEngine::Renderer::setClearColor(66.0f/255, 170.0f/255, 255.0f/255, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
      //timing

      auto currentTime = std::chrono::high_resolution_clock::now();
      deltaTime = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();

      //render
      RenderEngine::Renderer::clear();

      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
        glfwSetWindowShouldClose(window, true);
      }
      
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        view = glm::translate(view, glm::vec3(0.f, -0.1f,   0.0f) * (float)deltaTime);
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        view = glm::translate(view, glm::vec3(0.f, 0.1f, 0.0f) *  (float)deltaTime);
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        view = glm::translate(view, glm::vec3(-0.1f, 0.f,   0.0f) * (float)deltaTime);
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        view = glm::translate(view, glm::vec3(0.1f, 0.f, 0.0f) *  (float)deltaTime);
      if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.1f) * (float)deltaTime);
      if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        view = glm::translate(view, glm::vec3(0.0f, 0.0f,  0.1f) * (float)deltaTime);

      float pos = glfwGetTime() / 5.f * gWindowSize.y / 500;
      if (pos >= 1.3f)
      {
        glfwSetTime(0);
      }

      rotation += glm::vec3(0.0f, 0.0f, sin(glfwGetTime())/10);

      shader->use();
      shader->setFloat(pos, "pos");

      shader->setMat4(view, "viewMatrix");

      sprite->render(glm::vec3(0.f, 0.f, 0.0f), glm::vec3(1.0f), rotation);

      glfwSwapBuffers(window);

      //timing

      lastTime = std::chrono::high_resolution_clock::now();

      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
  }
}
