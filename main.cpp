#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>
#include "Shader.h"
#include <GLFW/glfw3.h>

const int WIDTH = 1600;
const int HEIGHT = 900;

int main() {

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow *window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello GL", nullptr, nullptr);
    if (!window)
        return -1;

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return -1;

    float vertices[]{
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,     //0
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,     //1
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,    //2
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,   //3
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,    //4
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f     //5
    };

    unsigned int indices[]{
            0, 1, 5, // 1
            1, 4, 5, // 2
            1, 2, 4, // 3
            2, 3, 4 // 4
    };


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader("shader/shader.vs", "shader/shader.fs");
    shader.setFloat("timeColor", 1);

    glBindVertexArray(VAO);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        shader.use();
//        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;

}
