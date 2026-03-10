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

