#include "SpriteAnimation.h"


SpriteAnimation::SpriteAnimation(JsonValue animInfos)
{
	listFrame = std::vector<std::vector<int>>();
	int ymin;
	int ymax;
	switch (animInfos.getTag()) {
		case JSON_OBJECT:
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
				if (std::string("images").compare(i->key) == 0 && i->value.getTag() == JSON_ARRAY) {
					for (auto frame : i->value) {
						std::vector<int> vec = std::vector<int>();
						if (frame->value.getTag() == JSON_ARRAY) {
							for (auto nb : frame->value) {
								vec.push_back((int)nb->value.toNumber());
							}
						}
						vec.push_back(ymin);
						vec.push_back(ymax);
						std::copy(vec.begin(), vec.end(),
							std::ostream_iterator<int>(std::cout, " "));
						listFrame.push_back(vec);
					}
				}

			}
			break;
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
