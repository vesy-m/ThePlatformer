#include "GraphicsSystem.h"

namespace GameSystems {
	GraphicsSystem::GraphicsSystem()
	{
	}


	GraphicsSystem::~GraphicsSystem()
	{
	}

	int GraphicsSystem::Update(double dt, std::list<GameObjects::BaseGameObject*>& listObjects)
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor3f(1.0f, 1.0f, 1.0f);
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::SPRITE);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Update();
			}
		}
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::DEBUGVECTOR);
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
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::DEBUGVECTOR);
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
