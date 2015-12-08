#include "SpriteAnimation.h"
#include "debugManager.h"

namespace GameTools {
	SpriteAnimation::SpriteAnimation(JsonValue &animInfos)
	{
		if (animInfos.getTag() != GameTools::JSON_OBJECT) {
			GameTools::debugManager::getInstance().dAssert("anim is not an array");
		}
		listCoordSpriteByFrame = std::vector<std::vector<int>>();
		int ymin;
		int ymax;
		for (auto i : animInfos) {
			printf("%s = ", i->key);
			if (std::string("name").compare(i->key) == 0) {
				this->name = i->value.toString();
			}
			if (std::string("time").compare(i->key) == 0) {
				this->time = (int)i->value.toNumber();
			}
			if (std::string("ymin").compare(i->key) == 0) {
				ymin = (int)i->value.toNumber();
			}
			if (std::string("ymax").compare(i->key) == 0) {
				ymax = (int)i->value.toNumber();
			}
			if (std::string("images").compare(i->key) == 0 && i->value.getTag() == GameTools::JSON_ARRAY) {
				for (auto frame : i->value) {
					std::vector<int> vec = std::vector<int>();
					if (frame->value.getTag() == GameTools::JSON_ARRAY) {
						for (auto nb : frame->value) {
							vec.push_back((int)nb->value.toNumber());
						}
					}
					vec.push_back(ymin);
					vec.push_back(ymax);
					std::copy(vec.begin(), vec.end(),
						std::ostream_iterator<int>(std::cout, " "));
					listCoordSpriteByFrame.push_back(vec);
				}
			}

		}
	}

	SpriteAnimation::SpriteAnimation()
	{
	}

	SpriteAnimation::~SpriteAnimation()
	{
	}

	std::string SpriteAnimation::getName()
	{
		return this->name;
	}

	int SpriteAnimation::getSpriteXmin(int numFrame)
	{
		return this->listCoordSpriteByFrame[numFrame][0];
	}

	int SpriteAnimation::getSpriteXmax(int numFrame)
	{
		return this->listCoordSpriteByFrame[numFrame][1];
	}

	int SpriteAnimation::getSpriteYmin(int numFrame)
	{
		return this->listCoordSpriteByFrame[numFrame][2];
	}

	int SpriteAnimation::getSpriteYmax(int numFrame)
	{
		return this->listCoordSpriteByFrame[numFrame][3];
	}

	int SpriteAnimation::getTime()
	{
		return this->time;
	}

	int SpriteAnimation::getSizeListFrame()
	{
		return (int) this->listCoordSpriteByFrame.size();
	}
}
