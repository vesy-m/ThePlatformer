#pragma once
#include "Texture.h"
#include "GameEngine.h"
#include <vector>

class Level
{
public:
	Level();
	~Level();
	void putObjectDepthOrdered(GameObjects::BaseGameObject * obj);
	std::list<GameObjects::BaseGameObject*>& getObjects();
	std::vector<GameObjects::BaseGameObject*> getPlayers();
private:
	Texture *background;
	std::list<GameObjects::BaseGameObject *> listGameObject;
	int x;
	int y;
	float scale;
};

