#include "checkError.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <assert.h>

void checkErr()
{
	std::string errorCode = "";
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		switch (errCode)
		{
		case GL_INVALID_ENUM:
			errorCode = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorCode = "GL_INVALID_VALUE";
			break;

		case GL_INVALID_OPERATION:
			errorCode = "GL_INVALID_OPERATION";
			break;

		case GL_OUT_OF_MEMORY:
			errorCode = "GL_OUT_OF_MEMORY";
			break;

		default:
			errorCode = "UNKNOWN";
			break;
		}

		//根据传入的布尔值决定程序是否停止
		assert(false);
	}
}