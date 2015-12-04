#include <SFML/Window.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/OpenGL.hpp>
#include "GameEngine.h"
#include "WindowInputSytem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "SpriteSheet.h"
#include "ObjectFactory.h"
#include "SoundManager.h"
#include "AudioSystem.h"

int main()
{
	try
	{
		GameEngine::Core core = GameEngine::Core();
		//systems
		GameSystems::WindowInputSytem *winInput = new GameSystems::WindowInputSytem();
		GameSystems::GraphicsSystem *graphics = new GameSystems::GraphicsSystem();
		GameSystems::PhysicsSystem *physics = new GameSystems::PhysicsSystem();
		GameSystems::AudioSystem *audio = new GameSystems::AudioSystem();

		core.Add((GameSystems::BaseSystem *)winInput);
		core.Add((GameSystems::BaseSystem *)physics);
		core.Add((GameSystems::BaseSystem *)graphics);
		core.Add((GameSystems::BaseSystem *)audio);
		GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/start_menu.json");

		//start
		core.Init();
		core.MainLoop();
	}
	catch (std::exception &e)
	{
		MessageBox(NULL, e.what(), "Error", 0);
	}
    return (0);
}