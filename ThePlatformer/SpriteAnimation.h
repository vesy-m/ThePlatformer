#pragma once
#include <vector>
#include "gason.h"

#include <string>
#include <string.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>

namespace GameTools {
	class SpriteAnimation
	{
	public:
		SpriteAnimation(JsonValue&);
		SpriteAnimation();
		~SpriteAnimation();
		std::string getName();
		int getSpriteXmin(int);
		int getSpriteXmax(int);
		int getSpriteYmin(int);
		int getSpriteYmax(int);
		int getTime();
		int getSizeListFrame();
		bool getIsRepeated();
	private:
		int time;
		std::string name;
		std::vector<std::vector<int>> listCoordSpriteByFrame;
		bool isRepeated;
	};
}
