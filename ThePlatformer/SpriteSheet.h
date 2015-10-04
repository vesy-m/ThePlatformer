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
#include "TextureManager.h"

class SpriteSheet
{
public:
	SpriteSheet(const std::string &jsonfileName);
	~SpriteSheet();
	std::string getExtension(const std::string & filename);
	int		parseSheetFile(JsonValue o);
	int		loadAndParseJsonFile(const std::string &filename);
	int		loadPngFile(const std::string &filename);
	bool	isAnimated();
	const SpriteAnimation & getAnim(const std::string & animName);
	Texture	*getTexture();
private:
	Texture			*texture;
	bool			animated;
	std::map<std::string, SpriteAnimation> anims;

};

