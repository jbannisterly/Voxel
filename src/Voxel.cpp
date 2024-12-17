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

    GLuint preVAO;
    glGenVertexArrays(1, &preVAO);
    glBindVertexArray(preVAO);

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

    GLuint textureBuffer;
    glGenFramebuffers(1, &textureBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, textureBuffer);

    GLuint targetTexture;
    glGenTextures(1, &targetTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, targetTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, targetTexture,0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    GLenum defertarget0 = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &defertarget0);

    GLuint postVAO;
    glGenVertexArrays(1, &postVAO);
    glBindVertexArray(postVAO);

    GLuint vertBufferScreen;
    float* verticesScreen = new float[18] {
        -1, -1, 0,
        1, -1, 0,
        -1, 1, 0,
        -1, 1, 0,
        1, -1, 0, 
        1, 1,  0
    };
    glGenBuffers(1, &vertBufferScreen);
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferScreen);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), verticesScreen, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint program = GLUtil::CreateProgram("src\\shaders\\VertexSimple.glsl", "src\\shaders\\FragmentSimple.glsl");
    GLuint postProgram = GLUtil::CreateProgram("src\\shaders\\VertexSimple.glsl", "src\\shaders\\FragmentPost.glsl");


    while(!glfwWindowShouldClose(window)){
        glBindFramebuffer(GL_FRAMEBUFFER, textureBuffer);
        glDisable(GL_BLEND);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(preVAO);
        glUseProgram(program);
        glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(postVAO);
        glUseProgram(postProgram);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}