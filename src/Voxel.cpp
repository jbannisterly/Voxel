#include <iostream>
#include "glad/include/glad/gl.h"
#include <GLFW/glfw3.h>

int main(){
    std::cout << "Hello World";
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

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertShaderSource = "#version 330 \n layout(location = 0) in vec3 pos;\n void main(){\ngl_Position =vec4(pos,1);\n}\0";
    glShaderSource(vertShader, 1, &vertShaderSource, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragShaderSource = "#version 330 \n out vec4 FragColor; \n void main(){\nFragColor = vec4(0,1,0,1);\n}\0";
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
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