#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <iostream>
#include <cmath>

#include "Resources/ResourceManager.h"

#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"

glm::ivec2 gWindowSize(960, 540);

GLfloat vertices[] = {
  //X      Y     Z     R     G     B     U     V
  -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 0
  -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 1
   0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 2
   0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f  // 3
};

GLuint elements[] = {
  //  0---3
  //  | \ |
  //  1---2
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

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
  std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << "\n";

  
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
     
    auto shader = ResourceManager::loadShaders("DefaultShader", "res/shaders/vertex.vert", "res/shaders/fragment.frag");
    auto texture = ResourceManager::loadTexture("Grass", "res/textures/grass16x16.jpg", GL_REPEAT, GL_NEAREST);

    RenderEngine::VertexBufferLayout layout;
    layout.reserve(3);                       //Optimization
    layout.addElementLayoutFloat(3, false);
    layout.addElementLayoutFloat(3, false);
    layout.addElementLayoutFloat(2, false);

    RenderEngine::VertexBuffer buffer;
    buffer.init(vertices, sizeof(vertices));

    RenderEngine::IndexBuffer indexBuffer;
    indexBuffer.init(elements, 6);

    RenderEngine::VertexArray vertexArray;
    vertexArray.addBuffer(buffer, layout);

    vertexArray.bind();
    
    shader->use();
    shader->setInt(gWindowSize.x, "windowSizeX");
    shader->setInt(gWindowSize.y, "windowSizeY");

    shader->setInt(0, "tex");

    glClearColor(66.0f/255, 170.0f/255, 255.0f/255, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT);

      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
        glfwSetWindowShouldClose(window, true);
      }

      float pos = glfwGetTime() / 5.f * gWindowSize.y / 500;
      if (pos >= 1.3f)
      {
        glfwSetTime(0);
      }

      //float pos = sin(glfwGetTime());

      //std::cout << "Pos: " << pos << "\n";

      shader->use();
      shader->setFloat(pos, "pos");

      glActiveTexture(GL_TEXTURE0);
      texture->bind();
      vertexArray.bind();
      indexBuffer.bind(); 

      glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);

      glfwSwapBuffers(window);

      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
  }
}
