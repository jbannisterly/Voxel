#include <iostream>
#include "glad/include/glad/gl.h"
#include <GLFW/glfw3.h>
#include "IOUtil.hpp"

namespace GLUtil{
    GLuint CreateProgram(char* vertexShaderPath, char* fragmenShaderPath){
        GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
        GLchar* vertexShaderSource = IOUtil::ReadFile(vertexShaderPath);
        glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertShader);
        
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        GLchar* fragmentShaderSource = IOUtil::ReadFile(fragmenShaderPath);
        glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragShader);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        return program;
    }
}