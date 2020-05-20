
#include <iostream>
#include <string>

#include "common.h"
#include "shader.h"

// 声明按键函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(int argc, char * argv[]) {

    // glfw初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 此行用来给Mac OS X系统做兼容
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // 创建窗口,获取窗口上上下文
    GLFWwindow* window = glfwCreateWindow(mWidth, mHeight, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 通过glfw注册按键事件回调
    glfwSetKeyCallback(window, key_callback);

    // Load OpenGL Functions
    gladLoadGL();
//    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    // 查询GPU最大支持顶点个数
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    // 获取视口
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // 编译着色器程序
    Shader ourShader("res/vert.vert", "res/frag.frag");

    // 顶点输入
    GLfloat vertices[] = {
        // Positions            // Colors           //Texture
        0.5f,   0.5f,   0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        0.5f,   -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f,  -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f,   0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };
    
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // 顶点数组对象 Vertex Array Object, VAO
    // 顶点缓冲对象 Vertex Buffer Object，VBO
    // 索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO
    GLuint VAO, VBO, VEO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VEO);
    
    glBindVertexArray(VAO);
    
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 设置顶点position属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // 设置顶点color属性指针
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    // 设置纹理texture属性指针
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glBindVertexArray(0);

    // 使用线框模式进行渲染
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    GLuint texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int w, h, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(std::string("res/textures/container.jpg").c_str(), &w, &h, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(std::string("res/textures/awesomeface.png").c_str(), &w, &h, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    ourShader.use();
    
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);

    // 渲染
    while (!glfwWindowShouldClose(window))
    {
        // 检查事件
        glfwPollEvents();

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        glm::mat4 trans = glm::mat4(1.0f);
//        trans = glm::rotate(trans, glm::radians(-90.f), glm::vec3(0.0, 0.0, 1.0));
//        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        
        //围绕Z轴旋转
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        
        auto ptr = glm::value_ptr(trans);
        std::cout << ptr[0];
        std::cout << ptr[1];
        std::cout << ptr[2];
        std::cout << ptr[3];

        ourShader.use();
    
        unsigned int transformLocation = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));
        
//        // 更新uniform颜色
//        float timeValue = glfwGetTime();
//        float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        // 绘图
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // 交换缓冲
        glfwSwapBuffers(window);
    }

    // 释放VAO,VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // 释放GLFW分配的内存
    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
    // 关闭应用程序
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
