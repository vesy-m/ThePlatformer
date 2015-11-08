#include "Texture.h"

namespace GameTools {
	Texture::Texture(const std::string& filename, GLuint &textureId, unsigned int width, unsigned int height)
	{
		this->filename = filename;
		this->textureId = textureId;
		this->width = width;
		this->height = height;
	}

	Texture::~Texture()
	{
	}

	GLuint Texture::getId()
	{
		return this->textureId;
	}

	unsigned int Texture::getWidth()
	{
		return this->width;
	}

	unsigned int Texture::getHeight()
	{
		return this->height;
	}

	const std::string & Texture::getFilename()
	{
		return this->filename;
	}
}
