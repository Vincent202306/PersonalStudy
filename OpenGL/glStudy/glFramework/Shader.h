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

private:

	GLuint program_ = 0;


};