#pragma once

#include <SFML\OpenGL.hpp>
#include <string>
#include <map>
#include "Texture.h"
#include <il.h>
#include <iostream>
#include <stdexcept>
#include "Singleton.h"

namespace GameTools {
	class TextureManager : public CSingletonStaticAlloc<TextureManager>
	{
		friend class CSingletonStaticAlloc<TextureManager>;
	public:
		void					loadTexture(const std::string &);
		Texture		*getTexture(const std::string&);
		~TextureManager();

	private:
		TextureManager();
		TextureManager(TextureManager const&) = delete;
		void operator=(TextureManager const&) = delete;

		std::map<std::string, Texture> textureMap;
	};
}
