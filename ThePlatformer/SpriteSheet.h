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

namespace GameTools{
	class SpriteSheet
	{
	public:
		SpriteSheet(const std::string&);
		~SpriteSheet();
		std::string getExtension(const std::string&);
		int		parseSheetFile(JsonValue);
		int		loadAndParseJsonFile(const std::string&);
		int		loadPngFile(const std::string&);
		bool	isAnimated();
		const	SpriteAnimation & getAnim(const std::string&);
		Texture	*getTexture();
	private:
		Texture			*texture;
		bool			animated;
		std::map<std::string, SpriteAnimation> anims;
	};
}


