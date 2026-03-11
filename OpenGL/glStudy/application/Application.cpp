#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include <iostream>
//初始化静态变量

Application* Application::instance_ = nullptr;

Application::Application()
{

}

Application::~Application()
{

}

Application* Application::getInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}

	return instance_;
}

bool Application::init(const int& width,const int& height)
{
	//1 初始化GLFW的基本环境
	glfwInit();
	//1.1 设置OpenGL主版本号和次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//1.2 设置OpenGL启用核心模式(非立即渲染模式)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//2 创建窗体对象
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLWindow", nullptr, nullptr);
	if (window == nullptr)
		return false;

	glfwMakeContextCurrent(window);//设置当前窗体为opengl绘制的舞台

	//使用glad加载所有当前版本opengl的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	window_ = window;

	//订阅窗体大小变化事件
	glfwSetFramebufferSizeCallback(window_, frameBufferSizeCallback);
	//订阅键盘按下事件
	glfwSetKeyCallback(window_, keyCallback);

	glfwSetWindowUserPointer(window_, this);
	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(window_))
	{
		return false;
	}

	//接受并分发窗口消息
	glfwPollEvents();
	//切换双缓存
	glfwSwapBuffers(window_);

	return true;
}

bool Application::destroy()
{
	//4 退出程序前做相关清理
	glfwTerminate();
	return true;
}


void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application* application = (Application*)glfwGetWindowUserPointer(window);
	if (application != nullptr && application->resizeCallback_ != nullptr)
	{
		application->resizeCallback_(width, height);
	}
}

void Application::keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
{
	Application* application = (Application*)glfwGetWindowUserPointer(window);
	if (application != nullptr && application->keyCallback_ != nullptr)
	{
		application->keyCallback_(key, scanCode, action, mode);
	}
}