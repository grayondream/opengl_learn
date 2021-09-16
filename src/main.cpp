
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
#define WINDOW_TITLE "grayondream window"

//作为windows resize操作时的callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//键盘和鼠标事件
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    printf("hello opengl!\n");
    if(!glfwInit()){
        fprintf(stderr, "initialize glfw env error!\n");
        exit(-1);
    }    

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //创建glfw的窗口
    GLFWwindow *pwin = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if(nullptr == pwin){
        fprintf(stderr, "can not create window!\n");
        exit(-1);
    }

    glfwMakeContextCurrent(pwin);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        fprintf(stderr, "Failed to initialize GLAD");
        return -1;
    }

    //创建gl的view
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    while(!glfwWindowShouldClose(pwin)){
        processInput(pwin);

        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(pwin);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}