// main.cpp: 定义应用程序的入口点。
//

#include "main.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace std;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	//std::cout << "width:" << width << ",height" << height << endl;
	glViewport(0, 0, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
{
	if (key == GLFW_KEY_W)
	{
		cout << "press key w" << endl;
	}
}

int main()
{

	//1 初始化GLFW的基本环境
	glfwInit();
	//1.1 设置OpenGL主版本号和次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//1.2 设置OpenGL启用核心模式(非立即渲染模式)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//2 创建窗体对象
	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGLWindow", nullptr, nullptr);
	if (window == nullptr)
		return 0;

	glfwMakeContextCurrent(window);//设置当前窗体为opengl绘制的舞台

	//订阅窗体大小变化事件
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	//订阅键盘按下事件
	glfwSetKeyCallback(window, KeyCallback);

	//使用glad加载所有当前版本opengl的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	//设置opengl视口
	glViewport(0, 0, 20, 20);
	//设置清理颜色
	glClearColor(0.1, 0.2, 0.3, 0);
	
	//3 执行窗体循环 每次循环处理事件消息队列 -- 一帧
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//接受并分发窗口消息
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	//4 退出程序前做相关清理
	glfwTerminate();
	return 0;
}
