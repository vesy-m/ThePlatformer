#include "Texture.h"


Texture::Texture(GLuint &textureId, unsigned int width, unsigned int height)
{
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
