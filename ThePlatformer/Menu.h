#pragma once

#include <list>
#include "BaseGameObject.h"

class Menu
{
public:
	Menu();
	~Menu();
	std::string fileName;
	std::string prevMenu;
	int prevState;
	std::list<GameObjects::BaseGameObject*>& getObjects();
	void addButton(GameObjects::BaseGameObject *button);
private:
	std::list<GameObjects::BaseGameObject *> listButton;
};

