
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.h"
#include "glog.h"

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
    ilog("hello opengl");    
    if(!glfwInit()){
        elog("initialize glfw env error!");
        exit(-1);
    }    
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //创建glfw的窗口
    GLFWwindow *pwin = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if(nullptr == pwin){
        elog("can not create window!");
        exit(-1);
    }

    glfwMakeContextCurrent(pwin);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        elog("Failed to initialize GLAD");
        return -1;
    }

    int ret = 1;
    char error[256] = {0};
    //顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    string vshaderSource = GUtils::read_file("../glsl/vshader.glsl");
    const char *pvshaderSrc = vshaderSource.c_str();
    glShaderSource(vertexShader, 1, &pvshaderSrc, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ret);
    if(!ret){
        glGetShaderInfoLog(vertexShader, sizeof(error), nullptr, error);
        elog(error);
        exit(-1);
    }

    //片段着色器
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    string fshaderSource = GUtils::read_file("../glsl/fshader.glsl");
    const char *pfshaderSrc = fshaderSource.c_str();
    glShaderSource(fragShader, 1, &pfshaderSrc, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &ret);
    if(!ret){
        glGetShaderInfoLog(fragShader, sizeof(error), nullptr, error);
        elog(error);
        exit(-1);
    }

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &ret);
    if(!ret) {
        glGetProgramInfoLog(shaderProgram, sizeof(error), NULL, error);
        elog(error);
        exit(-1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    //三角形的顶点数据
    float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = { // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    
    //创建相关的着色器，以及着色器程序
    GLuint vbo = -1, vao = -1, ebo = -1;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);   
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //创建gl的view
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    while(!glfwWindowShouldClose(pwin)){
        processInput(pwin);

        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(pwin);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}