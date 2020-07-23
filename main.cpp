#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {

  const char *vertexShaderSource =
      R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main() {
   gl_Position = vec4(aPos, 1.0);
}
)";

  const char *fragmentShaderSource =
      R"(
#version 330 core
out vec4 FragColor;

void main()
{
  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

  GLFWwindow *window = nullptr;

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(1600, 900, "Hey Marlee", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
    return -1;

  float vertices[] = {
      // first triangle
      0.5f, 0.5f, 0.0f,  // top right
      0.5f, -0.5f, 0.0f, // bottom right
      -0.5f, 0.5f, 0.0f, // top left
      // second triangle //TODO Not working do EBO
      0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f, 0.0f   // top left
  };

  unsigned int VBO;

  glGenBuffers(1, &VBO);
  std::cout << "MEOW" << std::endl; // TODO LUL
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // VERTEX SHADER
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  int vsSuccess; // vertex shader success
  char vsInfoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vsSuccess);
  if (!vsSuccess) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, vsInfoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << vsInfoLog << std::endl;
  }
  // FRAGMENT SHADER
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  int fsSuccess; // fragment shader success
  char fsInfoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fsSuccess);
  if (!fsSuccess) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, fsInfoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << vsInfoLog << std::endl;
  }
  // Shader program (linking shaders)
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int spSuccess; // fragment shader success
  char spInfoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &spSuccess);
  if (!spSuccess) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, spInfoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
              << spInfoLog << std::endl;
  }

  glUseProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(.25, 1, 0.5, .5);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}