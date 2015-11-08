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

int main()
{
	GameEngine::Core core = GameEngine::Core();
	//systems
	GameSystems::WindowInputSytem *winInput = new GameSystems::WindowInputSytem();
	GameSystems::GraphicsSystem *graphics = new GameSystems::GraphicsSystem();
	GameSystems::PhysicsSystem *physics = new GameSystems::PhysicsSystem();

	core.Add((GameSystems::BaseSystem *)winInput);
	core.Add((GameSystems::BaseSystem *)physics);
	core.Add((GameSystems::BaseSystem *)graphics);
	GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/main_menu.json");
	
	//a enlever de commentaire pour corriger frame rate
	sf::Music music;
	if (!music.openFromFile("./assets/audio/dr_wily_stage.ogg"))
		return -1;
	music.setVolume(5);
	music.play();

	//start
	core.Init();
	core.MainLoop();

    return (0);
}