#include "JSONParser.h"
#include "SpriteSheet.h"

namespace GameTools {
	SpriteSheet::SpriteSheet(const std::string & filename)
	{
		std::string extension = getExtension(filename);
		if (std::string("json").compare(extension) == 0) {
			animated = true;
			loadAndParseJsonFile(filename);
		}
		else if (std::string("png").compare(extension) == 0) {
			animated = false;
			loadPngFile(filename);
		}

	}

	SpriteSheet::~SpriteSheet()
	{

	}

	std::string SpriteSheet::getExtension(const std::string& filename) {
		return filename.substr(filename.find_last_of(".") + 1);
	}

	int			SpriteSheet::parseSheetFile(JsonValue o) {
		switch (o.getTag()) {
		case JSON_OBJECT:
			for (auto i : o) {
				printf("%s = ", i->key);
				if (std::string("file").compare(i->key) == 0) {
					this->texture = TextureManager::getInstance().getTexture(i->value.toString());
				}
				if (std::string("anim").compare(i->key) == 0) {
					if (i->value.getTag() != GameTools::JSON_ARRAY) {
						GameTools::debugManager::getInstance().dAssert("anim is not an array");
					}
					for (auto an : i->value) {
						SpriteAnimation anim = SpriteAnimation(an->value);
						this->anims[anim.getName()] = anim;
					}
				}

			}
			break;
		}
		return 0;
	}

	int			SpriteSheet::loadAndParseJsonFile(const std::string &filename)
	{
		GameSystems::JSONParser parser(filename);
		parseSheetFile(parser.getJSONValue());
		return 0;
	}

	int			SpriteSheet::loadPngFile(const std::string & filename)
	{
		this->texture = TextureManager::getInstance().getTexture(filename);
		if (this->texture == NULL) throw std::exception();
		return 0;
	}

	bool		SpriteSheet::isAnimated()
	{
		return animated;
	}

	const SpriteAnimation &SpriteSheet::getAnim(const std::string & animName) {
		std::map<std::string, SpriteAnimation>::iterator it = this->anims.find(animName);
		if (it == this->anims.end())
		{
			GameTools::debugManager::getInstance().dAssert("anim name doesn't exist");
		}
		return it->second;
	}

	Texture		*SpriteSheet::getTexture()
	{
		return this->texture;
	}

}
