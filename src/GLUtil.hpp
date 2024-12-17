#include <iostream>
#include "glad/include/glad/gl.h"
#include <GLFW/glfw3.h>
#include "IOUtil.hpp"
#include <stdlib.h>

namespace GLUtil{
    GLuint CreateProgram(char* vertexShaderPath, char* fragmenShaderPath){
        char* debugMessage = (char*)malloc(sizeof(char) * 1024);

        GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
        GLchar* vertexShaderSource = IOUtil::ReadFile(vertexShaderPath);
        glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertShader);
        glGetShaderInfoLog(vertShader, 1024, NULL, debugMessage);
        std::cout << "Vertex shader \n" << debugMessage << '\n';
        free(vertexShaderSource);

        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        GLchar* fragmentShaderSource = IOUtil::ReadFile(fragmenShaderPath);
        glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragShader);
        glGetShaderInfoLog(fragShader, 1024, NULL, debugMessage);
        std::cout << "Fragment shader \n" << debugMessage << '\n';
        free(fragmentShaderSource);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        free(debugMessage);
        return program;
    }
}