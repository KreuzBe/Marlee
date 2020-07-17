#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void) {

  GLFWwindow *window = nullptr;

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(1600, 900, "Hey Marlee", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}