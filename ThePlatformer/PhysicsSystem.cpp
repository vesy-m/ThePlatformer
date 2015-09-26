#include "PhysicsSystem.h"

namespace GameSystems {
	PhysicsSystem::PhysicsSystem()
	{
	}


	PhysicsSystem::~PhysicsSystem()
	{
	}

	int PhysicsSystem::Update(float dt, std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::PHYSIC);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Update();
			}
		}
		return 0;
	}

	void PhysicsSystem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::PHYSIC);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Init();
			}
		}
	}

	void PhysicsSystem::SendMessage()
	{
	}
}