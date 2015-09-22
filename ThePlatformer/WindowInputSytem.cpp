#include "WindowInputSytem.h"

namespace GameSystems {
	WindowInputSytem::WindowInputSytem()
	{
	}


	WindowInputSytem::~WindowInputSytem()
	{
	}

	void WindowInputSytem::Update(float dt, std::vector<GameObjects::BaseGameObject> listObjects)
	{
		for each (GameObjects::BaseGameObject object in listObjects)
		{
			std::vector<GameObjects::BaseComponent*> componentList = object.getComponents("WINDOW");
		}
	}

	void WindowInputSytem::Init(void)
	{

	}
	void WindowInputSytem::SendMessage()
	{

	}
}