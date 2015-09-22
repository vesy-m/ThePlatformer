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
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::WINDOW);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Update();
			}
		}
	}

	void WindowInputSytem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::WINDOW);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Init();
			}
		}
	}
	void WindowInputSytem::SendMessage()
	{

	}
}