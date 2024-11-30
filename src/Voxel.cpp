#include <iostream>
#include <GLFW/glfw3.h>

int main(){
    std::cout << "Hello World";
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(512, 512, "Hello World", NULL, NULL);
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }
    return 0;
}