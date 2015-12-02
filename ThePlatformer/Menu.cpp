#include "Menu.h"



Menu::Menu()
{
	this->fileName = "";
	this->prevMenu = "";
	this->prevState = -1;
}


Menu::~Menu()
{
}


std::list<GameObjects::BaseGameObject *> &Menu::getObjects()
{
	return this->listButton;
}


void Menu::addButton(GameObjects::BaseGameObject *button)
{
	this->listButton.push_back(button);
}
