#include "WindowInputSytem.h"

namespace GameSystems {
	WindowInputSytem::WindowInputSytem()
	{
	}


	WindowInputSytem::~WindowInputSytem()
	{
	}
	
	void WindowInputSytem::Update(float dt, std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameObjects::BaseComponent*> componentList = object->getComponents("WINDOW");
		}
	}

	void WindowInputSytem::Init(void)
	{

	}
	void WindowInputSytem::SendMessage()
	{

	}
}