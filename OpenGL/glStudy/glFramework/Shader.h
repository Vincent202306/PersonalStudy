#pragma once
#include "core.h"
#include <string>

class Shader
{
public:


	Shader(const char*, const char*);

	~Shader();

	void begin();

	void end();

	void checkShaderError(GLuint, int);

	void setFloat(const std::string& name, float value);

	void setVector3f(const std::string& name, float x, float y, float z);

	void setVector3f(const std::string& name, float* vec);

	void setInt(const std::string& name, int value);

private:

	GLuint program_ = 0;


};