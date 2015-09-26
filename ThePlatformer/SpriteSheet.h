#pragma once

#include <SFML/OpenGL.hpp>
#include <string>
#include <map>
#include "SpriteAnimation.h"
#include "gason.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <il.h>

class SpriteSheet
{
public:
	SpriteSheet(std::string &jsonfileName);
	SpriteSheet();
	~SpriteSheet();
	char * readfile(std::string & jsonfileName);
	double sum_and_print(JsonValue o);
	void loadTexture(const std::string filename);

	GLuint textureSpriteSheetID;
	int widthPixel;
	int heightPixel;
	std::string name;
	std::map<std::string, SpriteAnimation> anims;

};

