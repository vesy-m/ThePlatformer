#include "TextureManager.h"
#include "debugManager.h"

namespace GameTools {
	TextureManager::TextureManager()
	{
		// init DevIL. This needs to be done only once per application
		ilInit();
		textureMap = std::map<std::string, Texture>();
	}

	TextureManager::~TextureManager()
	{
	}

	void				TextureManager::loadTexture(const std::string &filename)
	{
		ILboolean		success;
		unsigned int	imageID;
		GLuint			textureId;

		ilGenImages(1, &imageID);
		ilBindImage(imageID);
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		success = ilLoadImage((ILstring)filename.c_str());
		if (!success) {
			GameTools::debugManager::getInstance().dAssert("png file not loaded : " + filename);
		}
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT),
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			ilGetData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		this->textureMap.insert(std::pair<std::string, Texture>(filename, Texture(filename, textureId, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT))));
	}

	Texture		*TextureManager::getTexture(const std::string & filename)
	{
		try {
			return &this->textureMap.at(filename);
		}
		catch (const std::out_of_range&) {
			loadTexture(filename);
			try {
				return &this->textureMap.at(filename);
			}
			catch (const std::out_of_range&) {
				std::cout << "impossible to load the texture" << std::endl;
				return NULL;
			}
		}
	}
}
