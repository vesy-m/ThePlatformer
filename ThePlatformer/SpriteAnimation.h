#pragma once
#include <vector>
#include "gason.h"

#include <string>
#include <string.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>

class SpriteAnimation
{
public:
	SpriteAnimation(JsonValue &animInfos);
	SpriteAnimation();
	~SpriteAnimation();
	std::string getName();
	int getSpriteXmin(int numFrame);
	int getSpriteXmax(int numFrame);
	int getSpriteYmin(int numFrame);
	int getSpriteYmax(int numFrame);
	int getTime();
	int getSizeListFrame();
private:
	int time;
	std::string name;
	std::vector<std::vector<int>> listCoordSpriteByFrame;
};

