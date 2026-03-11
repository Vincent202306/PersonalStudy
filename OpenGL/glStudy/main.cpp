// main.cpp: 定义应用程序的入口点。
//

#include "main.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "checkError.h"

#include "application/Application.h"


using namespace std;

void FrameBufferSizeCallback(int width, int height)
{
	//std::cout << "width:" << width << ",height" << height << endl;
	glViewport(0, 0, width, height);
}

void KeyCallback(int key, int scanCode, int action, int mode)
{
	if (key == GLFW_KEY_W)
	{
		cout << "press key w" << endl;
	}
}

void prepareVBO()
{
	//创建一个VBO
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));

	//销毁一个vbo
	GL_CALL(glDeleteBuffers(1, &vbo));

	//创建n个vbo
	GLuint vboArr[] = {0,0,0};
	GL_CALL(glGenBuffers(3, vboArr));

	//销毁n个vbo
	GL_CALL(glDeleteBuffers(3, vboArr));

}

void prepare()
{
	float vertices[] =
	{
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};
	//生成一个VBO
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));
	//绑定当前VBO到opengl状态机的当前vbo插槽上
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	//向vbo传输数据，也是在开辟显存
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
}

void prepareSingleBuffers()
{
	float positions[] =
	{
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};
	float colors[] =
	{
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f
	};

	GLuint posVbo = 0;
	GL_CALL(glGenBuffers(1, &posVbo));
	GLuint colorVbo = 0;
	GL_CALL(glGenBuffers(1, &colorVbo));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
}

int main()
{
	if (!app->init(800, 600))
	{
		return -1;
	}

	app->setResizeCallback(FrameBufferSizeCallback);

	app->setKeyCallback(KeyCallback);

	//设置opengl视口
	GL_CALL(glViewport(0, 0, 20, 20));
	//设置清理颜色
	GL_CALL(glClearColor(0.1, 0.2, 0.3, 0));
	
	//3 执行窗体循环 每次循环处理事件消息队列 -- 一帧
	while (app->update())
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
		//GL_CALL(glClear(-1));
		

		//渲染操作
	}

	return app->destroy() ? 0 : -1;
}
