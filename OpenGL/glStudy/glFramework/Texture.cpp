#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "StbImage/stb_image.h"

Texture::Texture(const std::string& path, unsigned int unit) :path_(path), unit_(unit) 
{
	//1.stbImage 读取图片
	stbi_set_flip_vertically_on_load(true);//设置y轴反转，因为OpenGL的预期是从左下角读取纹理像素颜色
	stbi_uc* data = stbi_load(path.c_str(), &width_, &height_, &(this->comp_), STBI_rgb_alpha);

	//2.生成纹理对象且激活单元并绑定
	glGenTextures(1, &texture_);
	glActiveTexture(GL_TEXTURE0 + this->unit_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	//3.传输纹理数据,开辟显存
	int width = width_;
	int height = height_;
	for (int level = 0; true; ++level)
	{
		glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		if (width == 1 && height == 1)
		{
			break;
		}

		width = width > 1 ? width / 2 : 1;
		height = height > 1 ? height / 2 : 1;
	}
	

	stbi_image_free(data);//释放从cpu端内存数据

	//4.设置纹理的过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	//5.设置纹理包裹方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u方向
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//v方向
}

Texture::~Texture()
{
	if (texture_ != 0)
	{
		glDeleteTextures(1, &texture_);
	}
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + unit_);
	glBindTexture(GL_TEXTURE_2D, texture_);
}