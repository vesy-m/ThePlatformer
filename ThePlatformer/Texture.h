#pragma once

#include <SFML\OpenGL.hpp>

class Texture
{
public:
	Texture(GLuint &, unsigned int, unsigned int);
	~Texture();
	GLuint getId();
	unsigned int getWidth();
	unsigned int getHeight();
private:
	GLuint textureId;
	unsigned int width;
	unsigned int height;
};

