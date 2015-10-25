#include "Level.h"



Level::Level()
{
}


Level::~Level()
{
}


void Level::putObjectDepthOrdered(GameObjects::BaseGameObject * obj) {
	int depth = obj->getDepth();
	int size = this->listGameObject.size();


	for (std::list<GameObjects::BaseGameObject *>::iterator it = this->listGameObject.begin(); it != this->listGameObject.end(); ++it) {
		if ((*it)->getDepth() <= depth) {
			this->listGameObject.insert(it, obj);
			return;
		}
	}
	this->listGameObject.push_back(obj);
}

std::list<GameObjects::BaseGameObject *> &Level::getObjects()
{
	return this->listGameObject;
}

std::vector<GameObjects::BaseGameObject *> Level::getPlayers()
{
	std::vector<GameObjects::BaseGameObject *> playersList = std::vector<GameObjects::BaseGameObject *>();
	for (std::list<GameObjects::BaseGameObject *>::iterator it = this->listGameObject.begin(); it != this->listGameObject.end(); ++it) {
		if ((*it)->getType() == GameObjects::objectType::PLAYER) {
			playersList.push_back((*it));
		}
	}
	
	return playersList;
}
