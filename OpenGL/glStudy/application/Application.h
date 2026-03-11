#pragma once
#include <iostream>
#define app Application::getInstance()

class GLFWwindow;

using OnResize = void (*)(int width, int height);

typedef void (*OnKey)(int key, int scanCode, int action, int mode);

class Application {

public:

	virtual ~Application();

	static Application* getInstance();

	uint32_t getWidth()const { return width_; }
	uint32_t getHeight()const { return height_; }


	bool init(const int& width, const int& height);

	bool update();

	bool destroy();

	inline void setResizeCallback(OnResize callback)
	{
		resizeCallback_ = callback;
	}
	inline void setKeyCallback(OnKey callback)
	{
		keyCallback_ = callback;
	}

private:

	Application();

	static Application* instance_;

	uint32_t width_ = 0;
	uint32_t height_ = 0;

	GLFWwindow* window_ = nullptr;

	OnResize resizeCallback_ = nullptr;

	OnKey keyCallback_ = nullptr;



	static void frameBufferSizeCallback(GLFWwindow*, int width, int height);

	static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode);

};