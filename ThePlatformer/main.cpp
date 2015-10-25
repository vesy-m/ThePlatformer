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

int main()
{
	GameEngine::Core core = GameEngine::Core();
	//systems
	GameSystems::WindowInputSytem *winInput = new GameSystems::WindowInputSytem();
	GameSystems::GraphicsSystem *graphics = new GameSystems::GraphicsSystem();
	GameSystems::PhysicsSystem *physics = new GameSystems::PhysicsSystem();

	core.Add((GameSystems::System *)winInput);
	core.Add((GameSystems::System *)physics);
	core.Add((GameSystems::System *)graphics);
	core.LoadLevelFile("level2.json");
	
	//a enlever de commentaire pour corriger frame rate
	/*
	sf::Music music;
	if (!music.openFromFile("dr_wily_stage.ogg"))
		return -1;
	music.setVolume(10);
	music.play();
	*/

	//start
	core.Init();
	core.MainLoop();

    return (0);
}