#pragma once
#include <iostream>
#define app Application::getInstance()

class Application {

public:

	virtual ~Application();

	static Application* getInstance();

	void test()
	{
		std::cout << "test" << std::endl;
	}

private:

	Application();

	static Application* instance_;
};