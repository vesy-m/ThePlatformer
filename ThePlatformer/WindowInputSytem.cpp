#include "WindowInputSytem.h"

namespace GameSystems {
	WindowInputSytem::WindowInputSytem()
	{
		this->fullscreen = false;
	}


	WindowInputSytem::~WindowInputSytem()
	{

	}
	
	int WindowInputSytem::Update(double dt, std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		sf::Event event;
		bool changeSize = false;


		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return 1;
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::F11)
				{
					changeSize = true;
					break;
				}
			}

			for each (GameObjects::BaseGameObject* object in listObjects)
			{
				std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::WINDOW);
				for each (GameComponents::BaseComponent* component in componentList) ((GameComponents::InputComponent *)component)->UpdateInputState(event, dt);
			}
		}

		if (changeSize == true) {
			this->fullscreen = !this->fullscreen;
			if (this->fullscreen) {
				window->create(sf::VideoMode::getDesktopMode(), "ThePlatformer", sf::Style::Fullscreen, sf::ContextSettings(32));
			}
			else {
				window->create(sf::VideoMode(1280, 720), "ThePlatformer", sf::Style::Close, sf::ContextSettings(32));
			}
		}

		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::WINDOW);
			for each (GameComponents::BaseComponent* component in componentList) component->Update(dt);
		}
		window->display();
		return 0;
	}

	void WindowInputSytem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		this->window = new sf::Window(sf::VideoMode(1280, 720), "ThePlatformer", sf::Style::Close, sf::ContextSettings(32));
		window->setVerticalSyncEnabled(false);
		window->setKeyRepeatEnabled(true);
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::WINDOW);
			for each (GameComponents::BaseComponent* component in componentList) component->Init();
		}
	}

	//have to receive message in case of change in window like size...
	void WindowInputSytem::SendMessage()
	{

	}
}