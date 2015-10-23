#pragma once
#include "Texture.h"
#include "GameEngine.h"


class Level
{
public:
	Level();
	~Level();
	void putObjectDepthOrdered(GameObjects::BaseGameObject * obj);
	std::list<GameObjects::BaseGameObject*>& getObjects();
	int getX();
	int getY();
	void setX(int);
	void setScale(float);
	float getScale();
private:
	Texture *background;
	std::list<GameObjects::BaseGameObject *> listGameObject;
	int x;
	int y;
	float scale;
};

