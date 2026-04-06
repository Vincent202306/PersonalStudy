#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Shader::Shader(const char* vertexShaderPath,const char* fragmentShaderPath)
{
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string vertexShaderCode, fragmentShaderCode;

	try
	{
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		std::stringstream vertexShaderStream, fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderCode = vertexShaderStream.str();
		fragmentShaderCode = fragmentShaderStream.str();
		vertexShaderFile.close();
		fragmentShaderFile.close();

		const char* vertexShaderSource = vertexShaderCode.c_str();
		const char* fragmentShaderSource = fragmentShaderCode.c_str();

		GLuint vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderObj, 1, &vertexShaderSource, NULL);

		GLuint fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderObj, 1, &fragmentShaderSource, NULL);

		
		glCompileShader(vertexShaderObj);
		checkShaderError(vertexShaderObj, GL_COMPILE_STATUS);

		glCompileShader(fragmentShaderObj);
		checkShaderError(fragmentShaderObj, GL_COMPILE_STATUS);

		//4. 创建一个program对象，管理shader对象,负责链接
		program_ = glCreateProgram();
		glAttachShader(program_, vertexShaderObj);
		glAttachShader(program_, fragmentShaderObj);
		glLinkProgram(program_);
		checkShaderError(program_, GL_LINK_STATUS);
		glDeleteShader(vertexShaderObj);
		glDeleteShader(fragmentShaderObj);
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}
}

Shader::~Shader()
{

}

void Shader::begin()
{
	glUseProgram(program_);
}

void Shader::end()
{
	glUseProgram(0);
}

void Shader::checkShaderError(GLuint target, int type)
{
	int success = 0;
	switch (type)
	{
	case GL_COMPILE_STATUS:
		glGetShaderiv(target, type, &success);
		if (!success)
		{
			char infoLog[512] = { 0 };
			glGetShaderInfoLog(target, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		break;

	case GL_LINK_STATUS:
		glGetProgramiv(target, type, &success);
		if (!success)
		{
			char infoLog[512] = { 0 };
			glGetProgramInfoLog(program_, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		break;
	default:
		break;
	}
}


void Shader::setFloat(const std::string& name, float value)
{
	GLuint location = glGetUniformLocation(program_, name.c_str());
	glUniform1f(location, value);
}

void Shader::setInt(const std::string& name, int value)
{
	GLuint location = glGetUniformLocation(program_, name.c_str());
	glUniform1i(location, value);
}

void Shader::setVector3f(const std::string& name, float x, float y, float z)
{
	GLuint location = glGetUniformLocation(program_, name.c_str());
	glUniform3f(location, x, y, z);
}

void Shader::setVector3f(const std::string& name, float* vec)
{
	GLuint location = glGetUniformLocation(program_, name.c_str());
	glUniform3fv(location, 1, vec);
}