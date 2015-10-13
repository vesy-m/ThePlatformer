#pragma once
#include "Texture.h"

class Level
{
public:
	Level(int);
	~Level();
private:
	Texture *background;
};

