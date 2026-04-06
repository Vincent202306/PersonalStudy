// main.cpp: 定义应用程序的入口点。
//

#include "main.h"
#include <iostream>
#include "glFramework/core.h"
#include "checkError.h"

#include "application/Application.h"
#include "glFramework/Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "StbImage/stb_image.h"

using namespace std;

//全局变量vao（管理渲染数据） program（管理渲染程序）
GLuint vao = 0;
Shader* shader = nullptr;
GLuint texture = 0;

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
	
	shader->setInt("sampler", 0);
	shader->setFloat("time", glfwGetTime());
	/*float color[] = { 0.3,0.4,0.5};
	shader->setVector3f("ucolor", color);*/
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
		-0.5f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
	};

	float uvs[] =
	{
		0.0f,0.0f,
		2.0f,0.0f,
		0.0f,1.0f,
		2.0f,1.0f,
	};

	float colors[] =
	{
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0,
		0.0,0.0,1.0
	};

	unsigned int indices[] =
	{
		0,1,2,
		2,1,3
	};

	// 2.创建一个vbo，管理顶点数据的显存
	GLuint posVbo,colorVbo,uvVbo = 0;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

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

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);
}


void prepareTexture()
{
	//1.stbImage 读取图片
	int width = 0;
	int height = 0;
	int comp = 0;
	// 设置stbi库加载图片的加载模式反转y轴
	stbi_set_flip_vertically_on_load(true);

	stbi_uc* data = stbi_load("assets/textures/raw.png", &width, &height, &comp, STBI_rgb_alpha);
	//2.生成纹理对象且激活单元并绑定
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//3.传输纹理数据,开辟显存
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


	//释放从cpu端内存数据
	stbi_image_free(data);

	//4.设置纹理的过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//5.设置纹理包裹方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//v
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
	prepareTexture();
	prepareShader();
	
	//3 执行窗体循环 每次循环处理事件消息队列 -- 一帧
	while (app->update())
	{
		render();	
	}

	return app->destroy() ? 0 : -1;
}
