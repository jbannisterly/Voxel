#include <iostream>
#include "glad/include/glad/gl.h"
#include <GLFW/glfw3.h>
#include "GLUtil.hpp"
#include "OBJUtil.hpp"

int main(){
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(512, 512, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL((GLADloadfunc)glfwGetProcAddress);
    glViewport(0, 0, 512, 512);

    OBJ test = OBJ(IOUtil::ReadFile("res\\test.obj"));

    GLuint vertBuffer;
    int nVertices;
    float* vertices = test.GetVertex(&nVertices);
    glGenBuffers(1, &vertBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(float), vertices, GL_STATIC_DRAW);

    GLuint indexBuffer;
    int nIndices;
    int* indices = test.GetIndex(&nIndices);
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(int), indices, GL_STATIC_DRAW);

    GLuint program = GLUtil::CreateProgram("src\\shaders\\VertexSimple.glsl", "src\\shaders\\FragmentSimple.glsl");

    glUseProgram(program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)){
        glClearColor(1,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}