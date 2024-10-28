#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <iostream>

glm::ivec2 gWindowSize(960, 540);

int main()
{
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
    glClearColor(66.0f/255, 170.0f/255, 255.0f/255, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT);

      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
        glfwSetWindowShouldClose(window, true);
      }

      glfwSwapBuffers(window);

      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
  }
}
