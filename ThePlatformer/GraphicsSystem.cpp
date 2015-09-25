#include "GraphicsSystem.h"

namespace GameSystems {
	GraphicsSystem::GraphicsSystem()
	{
	}


	GraphicsSystem::~GraphicsSystem()
	{
	}

	int GraphicsSystem::Update(float dt, std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::SPRITE);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Update();
			}
		}
		return 0;
	}

	void GraphicsSystem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::SPRITE);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Init();
			}
		}
	}

	void GraphicsSystem::SendMessage()
	{
	}
}
