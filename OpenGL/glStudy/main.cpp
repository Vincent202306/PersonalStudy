// main.cpp: 定义应用程序的入口点。
//

#include "main.h"
#include <iostream>
#include "glFramework/core.h"
#include "checkError.h"

#include "application/Application.h"
#include "glFramework/Shader.h"


using namespace std;

//全局变量vao（管理渲染数据） program（管理渲染程序）
GLuint vao = 0;
Shader* shader = nullptr;

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

void prepareSingBuffers1()
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
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	GLuint colorsVbo = 0;
	glGenBuffers(1, &colorsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void prepareInterleavedBuffer()
{
	float vertices[] =
	{
		-0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f, 0.0f,0.0f,1.0f
	};
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
}

void prepareInterleavedBuffer1()
{
	float vertices[] =
	{
		-0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f, 0.0f,0.0f,1.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}


void prepareInterleavedBuffer2()
{
	//pos and uv
	float vertices[] =
	{
		-0.5f,-0.5f,0.0f, 1.0f,0.0f,
		0.5f,-0.5f,0.0f, 0.0f,1.0f,
		0.0f,0.5f,0.0f, 0.0f,0.0f,
		0.5f,0.5f,0.0f, 0.0f,0.0f,
		0.8f,0.8f,0.0f, 0.0f,0.0f,
		0.8f,0.0f,0.0f, 0.0f,0.0f,
	};

	float colors[] =
	{
		-0.5f,-0.5f,0.0f,0.5,
		0.5f,-0.5f,0.0f,0.5,
		0.0f,0.5f,0.0f,0.5,
		0.0f,0.5f,0.0f,0.5,
		0.0f,0.5f,0.0f,0.5,
		0.0f,0.5f,0.0f,0.5,
	};

	GLuint verticesVbo = 0;
	glGenBuffers(1, &verticesVbo);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint colorVbo = 0;
	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)3);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void prepareShader()
{
	shader = new Shader("assets/shaders/vetex.glsl", "assets/shaders/fragment.glsl");
}


void render()
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	//渲染操作
	//GL_CALL(glUseProgram(program));
	shader->begin();
	shader->setFloat("time", glfwGetTime());
	GL_CALL(glBindVertexArray(vao));
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
	GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0)); 
	GL_CALL(glBindVertexArray(0));
	shader->end();
}

void prepareVao()
{
	//1. 准备顶点数据和索引数据
	float positions[] =
	{
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f,
		//0.5f,0.5f,0.0f,
	};

	float colors[] =
	{
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0
	};

	unsigned int indices[] =
	{
		0,1,2,
		//2,1,3
	};

	// 2.创建一个vbo，管理顶点数据的显存
	GLuint posVbo,colorVbo = 0;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//3. 创建一个ebo，管理索引数据的显存
	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//4. 创建一个vao，管理vbo和ebo的绑定关系，管理顶点属性配置
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//5. 配置顶点属性指针，让vao知道vbo中的数据该如何解析，告诉vao我需要启用哪个顶点属性
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);
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
	//prepareInterleavedBuffer2();
	prepareVao();
	prepareShader();
	
	//3 执行窗体循环 每次循环处理事件消息队列 -- 一帧
	while (app->update())
	{
		render();	
	}

	return app->destroy() ? 0 : -1;
}
