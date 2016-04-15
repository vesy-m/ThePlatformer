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
		typedef struct l {
			int height;
			int width;
			float xTexCoordMin;
			float xTexCoordMax;
			float yTexCoordMin;
			float yTexCoordMax;
		} Letter;

		SpriteSheet(const std::string&);
		~SpriteSheet();
		std::string getExtension(const std::string&);
		int		parseSheetFile(JsonValue);
		int		loadAndParseJsonFile(const std::string&);
		int		loadPngFile(const std::string&);
		bool	isAnimated();
		const	SpriteAnimation & getAnim(const std::string&);
		const	Letter			&getLetter(const char &c);
		Texture	*getTexture();
	private:
		Texture			*texture;
		bool			animated;
		std::map<std::string, SpriteAnimation> anims;
		Letter Alphabet[127];
	};
}


