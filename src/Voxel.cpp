#include <iostream>
#include "glad/include/glad/gl.h"
#include <GLFW/glfw3.h>
#include "GLUtil.hpp"

int main(){
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(512, 512, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL((GLADloadfunc)glfwGetProcAddress);
    glViewport(0, 0, 512, 512);

    GLuint vertBuffer;
    float vertices[] = {-0.5f, -0.5f, 0.f, 
                    0.5f, -0.5f, 0.f, 
                    0.f, 0.7f, 0.f};
    glGenBuffers(1, &vertBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint program = GLUtil::CreateProgram("src\\shaders\\VertexSimple.glsl", "src\\shaders\\FragmentSimple.glsl");

    glUseProgram(program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)){
        glClearColor(1,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}