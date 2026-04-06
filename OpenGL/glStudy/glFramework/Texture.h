#pragma once
#include "core.h"
#include <string>
class Texture
{
public:

	Texture(const std::string& path, unsigned int unit);

	~Texture();

	void bind();

	inline GLuint getTexture()const
	{
		return texture_;
	}

	inline float getWidth()const
	{
		return width_;
	}

	inline float getHeight()const
	{
		return height_;
	}

private:
	GLuint texture_ = 0;
	unsigned int unit_ = 0;
	std::string path_ = "";

	int width_ = 0;
	int height_ = 0;
	int comp_ = 0;
};