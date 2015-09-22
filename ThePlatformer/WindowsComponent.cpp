#include "WindowsComponent.h"


namespace GameComponents {
	WindowsComponent::WindowsComponent()
	{
	}


	WindowsComponent::~WindowsComponent()
	{
	}

	COMPONENT_TYPE WindowsComponent::getType()
	{
		return this->type;
	}

	void WindowsComponent::Update()
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
		//	if (event.type == sf::Event::Closed)
		//	{
		//		// end the program
		//		running = false;
		//	}
		//	//else if (event.type == sf::Event::Resized)
		//	//{
		//	//	// adjust the viewport when the window is resized
		//	//	glViewport(0, 0, event.size.width, event.size.height);
		//	//}
		}
		window->display();
	}
	void WindowsComponent::Init()
	{
		this->window = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
		window->setVerticalSyncEnabled(true);
	}
}
