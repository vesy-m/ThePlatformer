#pragma once

#include <SFML\OpenGL.hpp>
#include <string>

class Texture
{
public:
	Texture(const std::string&, GLuint &, unsigned int, unsigned int);
	~Texture();
	GLuint getId();
	unsigned int getWidth();
	unsigned int getHeight();
	const std::string &getFilename();
private:
	GLuint textureId;
	unsigned int width;
	unsigned int height;
	std::string filename;
};

