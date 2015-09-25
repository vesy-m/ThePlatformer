#include "WindowInputSytem.h"

namespace GameSystems {
	WindowInputSytem::WindowInputSytem()
	{
	}


	WindowInputSytem::~WindowInputSytem()
	{
	}
	
	int WindowInputSytem::Update(float dt, std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				return 1;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::WINDOW);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Update();
			}
		}
		window->display();
		return 0;
	}

	void WindowInputSytem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		this->window = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
		window->setVerticalSyncEnabled(true);
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::WINDOW);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Init();
			}
		}
	}

	//have to receive message in case of change in window like size...
	void WindowInputSytem::SendMessage()
	{

	}
}