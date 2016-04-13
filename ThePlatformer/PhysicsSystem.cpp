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
			GameComponents::BaseComponent *component = object->getComponent(GameComponents::COMPONENT_TYPE::PHYSIC);
			if (component) component->Update(dt);
			component = object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER);
			if (component) component->Update(dt);
			component = object->getComponent(GameComponents::COMPONENT_TYPE::MECHANIC);
			if (component) component->Update(dt);
		}
		return 0;
	}

	void PhysicsSystem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent* component = object->getComponent(GameComponents::COMPONENT_TYPE::PHYSIC);
			if (component) component->Init();
			component = object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER);
			if (component) component->Init();
		}
	}
	
	void PhysicsSystem::SendAMessage() {

	}
}