#include "PhysicsSystem.h"

namespace GameSystems {
	PhysicsSystem::PhysicsSystem()
	{
	}


	PhysicsSystem::~PhysicsSystem()
	{
	}

	int PhysicsSystem::Update(double dt, std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::PHYSIC);
			for each (GameComponents::BaseComponent* component in componentList) component->Update(dt);
			componentList = object->getComponents(GameComponents::COMPONENT_TYPE::COLLIDER);
			for each (GameComponents::BaseComponent* component in componentList) component->Update(dt);
		}
		return 0;
	}

	void PhysicsSystem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::PHYSIC);
			for each (GameComponents::BaseComponent* component in componentList) component->Init();
			componentList = object->getComponents(GameComponents::COMPONENT_TYPE::COLLIDER);
			for each (GameComponents::BaseComponent* component in componentList) component->Init();
		}
	}

	void PhysicsSystem::SendMessage()
	{
	}
}