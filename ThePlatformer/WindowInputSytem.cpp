#include "WindowInputSytem.h"
#include "AudioSystem.h"

namespace GameSystems {
	bool WindowInputSytem::fullscreen = true;

	WindowInputSytem::WindowInputSytem()
	{
		this->currentFullScreenState = WindowInputSytem::fullscreen;
		this->window = NULL;
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
			if (event.type == sf::Event::Closed) {
				sf::WindowHandle handle = this->window->getSystemHandle();
				ShowWindow(handle, SW_RESTORE);
				GameSystems::GraphicsSystem::Camera::getInstance().reInit();
				GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/quit_menu.json");
				break;
			}
			else if (event.type == sf::Event::LostFocus)
			{
				std::cout << "lost focus" << std::endl;
				sf::WindowHandle handle = this->window->getSystemHandle();
				ShowWindow(handle, SW_MINIMIZE);
				GameSystems::AudioSystem::_pause = true;
				if (GameSystems::ObjectFactory::getInstance().stateGame == GameSystems::ObjectFactory::gameState::LEVEL) {
					GameSystems::GraphicsSystem::Camera::getInstance().reInit();
					GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/pause_menu.json");
					GameSystems::AudioSystem::_pauseMenu = true;
					break;
				}
			}
			else if (event.type == sf::Event::GainedFocus)
				GameSystems::AudioSystem::_pause = false;
			else if (event.type == sf::Event::Resized)
			{
				window->setMouseCursorVisible(false);
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape && GameSystems::ObjectFactory::getInstance().stateGame == GameSystems::ObjectFactory::gameState::LEVEL)
				{
					GameSystems::GraphicsSystem::Camera::getInstance().reInit();
					GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/pause_menu.json");
					GameSystems::AudioSystem::_pauseMenu = true;
					break;
				}
			}
			else if (event.type == sf::Event::JoystickButtonReleased) {
				if (event.joystickButton.button == 7 && GameSystems::ObjectFactory::getInstance().stateGame == GameSystems::ObjectFactory::gameState::LEVEL)
				{
					GameSystems::GraphicsSystem::Camera::getInstance().reInit();
					GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/pause_menu.json");
					GameSystems::AudioSystem::_pauseMenu = true;
					break;
				}
			}
			for each (GameObjects::BaseGameObject* object in listObjects)
			{
				GameComponents::InputComponent *component = reinterpret_cast<GameComponents::InputComponent*>(object->getComponent(GameComponents::COMPONENT_TYPE::WINDOW));
				if (component && component->IsComponentActive()) component->UpdateInputState(event, dt);
				component = reinterpret_cast<GameComponents::InputComponent*>(object->getComponent(GameComponents::COMPONENT_TYPE::EDITOR_KEYBOARD));
				if (component && component->IsComponentActive()) component->UpdateInputState(event, dt);
			}
		}
		if (WindowInputSytem::fullscreen != this->currentFullScreenState) {
			this->currentFullScreenState = WindowInputSytem::fullscreen;
			switchFullScreen();
		}

		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent* component = object->getComponent(GameComponents::COMPONENT_TYPE::WINDOW);
			if (component) {
				if (component->IsComponentActive()) component->Update(dt);
			}
			component = object->getComponent(GameComponents::COMPONENT_TYPE::BANNER);
			if (component) {
				if (component->IsComponentActive()) component->Update(dt);
			}
			component = object->getComponent(GameComponents::COMPONENT_TYPE::AUTO_PLAY);
			if (component) {
				if (component->IsComponentActive()) component->Update(dt);
			}
			component = object->getComponent(GameComponents::COMPONENT_TYPE::EDITOR_KEYBOARD);
			if (component) component->Update(dt);
		}
		window->display();
		return 0;
	}

	void WindowInputSytem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		if (this->window == NULL) {
			if (this->currentFullScreenState) {
				std::cout << sf::VideoMode::getDesktopMode().height << " " << sf::VideoMode::getDesktopMode().width << std::endl;
				this->window = new sf::Window(sf::VideoMode::getDesktopMode(), "Ultimate Sports Battle X", sf::Style::Fullscreen, sf::ContextSettings(32));
			} else {
				this->window = new sf::Window(sf::VideoMode(1280, 720), "Ultimate Sports Battle X", sf::Style::Close, sf::ContextSettings(32));
			}
			window->setVerticalSyncEnabled(false);
			window->setKeyRepeatEnabled(true);
			window->setMouseCursorVisible(false);
		}
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent*component = object->getComponent(GameComponents::COMPONENT_TYPE::WINDOW);
			if (component) component->Init();
			component = object->getComponent(GameComponents::COMPONENT_TYPE::EDITOR_KEYBOARD);
			if (component) component->Init();
		}
	}

	//have to receive message in case of change in window like size...
	void WindowInputSytem::SendAMessage()
	{
	}

	void WindowInputSytem::switchFullScreen() {
		if (this->currentFullScreenState) {
			std::cout << sf::VideoMode::getDesktopMode().height << " " << sf::VideoMode::getDesktopMode().width << std::endl;
			window->create(sf::VideoMode::getDesktopMode(), "Ultimate Sports Battle X", sf::Style::Fullscreen, sf::ContextSettings(32));
		}
		else {
			window->create(sf::VideoMode(1280, 720), "Ultimate Sports Battle X", sf::Style::Close, sf::ContextSettings(32));
		}
		window->setMouseCursorVisible(false);
	}
}