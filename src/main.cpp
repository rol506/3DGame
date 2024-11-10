#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <iostream>
#include <cmath>

#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Resources/ResourceManager.h"
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

int main(int argc, char** argv)
{
  ResourceManager::setExecutablePath(argv[0]);
  std::cout << "Set executable path: " << argv[0] << "\n";

  if (!glfwInit())
  {
    std::cout << "glfwInit failed!\n";
    return 1;
  }

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

  {

    RenderEngine::VertexBufferLayout layout;
    layout.addElementLayoutFloat(3, false);
    layout.addElementLayoutFloat(3, false);
    layout.addElementLayoutFloat(2, false);

    RenderEngine::VertexBuffer buffer;
    buffer.init(vertices, sizeof(vertices));

    RenderEngine::IndexBuffer indexBuffer;
    indexBuffer.init(elements, sizeof(elements));

    RenderEngine::VertexArray vertexArray;
    vertexArray.addBuffer(buffer, layout);

    auto shader = ResourceManager::loadShaders("DefaultShader", "res/shaders/vertex.vert", "res/shaders/fragment.frag");
    auto texture = ResourceManager::loadTexture("BrickWall", "res/textures/wall.jpg");

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

      shader->setFloat(pos, "pos");

      glActiveTexture(GL_TEXTURE0);
      texture->bind();
      indexBuffer.bind(); 
      vertexArray.bind();
      shader->use();
      
      glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);

      glfwSwapBuffers(window);

      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
  }
}
