#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {

  const char *vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

  const char *fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "} ";

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

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

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

  while (!glfwWindowShouldClose(window)) {
    glClearColor(.25, 1, 0.5, .5);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}