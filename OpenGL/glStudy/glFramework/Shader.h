#pragma once
#include "core.h"

class Shader
{
public:


	Shader(const char*, const char*);

	~Shader();

	void begin();

	void end();

	void checkShaderError(GLuint, int);

private:

	GLuint program_ = 0;


};