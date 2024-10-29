#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <iostream>

#include "Resources/ResourceManager.h"
#include "Renderer/ShaderProgram.h"

glm::ivec2 gWindowSize(960, 540);

GLfloat vertices[] = {
  //X      Y     Z     R     G     B
  -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, // 0
  -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, // 1
   0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // 2
   0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f  // 3
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
    GLuint VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    auto shader = ResourceManager::loadShaders("DefaultShader", "res/shaders/vertex.vert", "res/shaders/fragment.frag");

    glClearColor(66.0f/255, 170.0f/255, 255.0f/255, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT);

      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
        glfwSetWindowShouldClose(window, true);
      }

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBindVertexArray(VAO);
      shader->use();
      
      glDrawElements(GL_TRIANGLES, sizeof(elements), GL_UNSIGNED_INT, nullptr);

      glfwSwapBuffers(window);

      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
  }
}
