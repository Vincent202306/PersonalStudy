// main.cpp: 定义应用程序的入口点。
//

#include "main.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "checkError.h"

#include "application/Application.h"


using namespace std;

//全局变量vao（管理渲染数据） program（管理渲染程序）
GLuint vao = 0;
GLuint program = 0;

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
	};

	float colors[] =
	{
		-0.5f,-0.5f,0.0f,0.5,
		0.5f,-0.5f,0.0f,0.5,
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
	/*const char* vertexShaderSource = R"(
		#version 330 core
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec3 aColor;
		out vec3 ourColor;
		void main()
		{
			gl_Position = vec4(aPos, 1.0);
			ourColor = aColor;
		}
	)";
	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		in vec3 ourColor;
		void main()
		{
			FragColor = vec4(ourColor, 1.0);
		}
	)";
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);*/

	//1. 准备好vs fs的源代码字符串
	const char* vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	//2. 创建一个shader对象，告诉opengl这是一个顶点着色器对象,管理shader源码,负责编译，管理编译后的目标文件
	GLuint vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObj, 1, &vertexShaderSource, NULL);


	//3. 创建一个shader对象，告诉opengl这是一个片段着色器对象,管理shader源码,负责编译，管理编译后的目标文件
	GLuint fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObj, 1, &fragmentShaderSource, NULL);

	int success = 0;
	glCompileShader(vertexShaderObj);
	glGetShaderiv(vertexShaderObj, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		char infoLog[512] = { 0 };
		glGetShaderInfoLog(vertexShaderObj, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glCompileShader(fragmentShaderObj);
	glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512] = { 0 };
		glGetShaderInfoLog(fragmentShaderObj, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//4. 创建一个program对象，管理shader对象,负责链接
	program = glCreateProgram();
	glAttachShader(program, vertexShaderObj);
	glAttachShader(program, fragmentShaderObj);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success)
	{
		char infoLog[512] = { 0 };
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShaderObj);
	glDeleteShader(fragmentShaderObj);	
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
	prepareInterleavedBuffer2();
	prepareShader();
	//3 执行窗体循环 每次循环处理事件消息队列 -- 一帧
	while (app->update())
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
		//GL_CALL(glClear(-1));
		

		//渲染操作
		glUseProgram(program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	return app->destroy() ? 0 : -1;
}
