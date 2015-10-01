#include <SFML/Window.hpp>
#include <SFML/Audio/Music.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "GameEngine.h"
#include "WindowInputSytem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "SpriteSheet.h"

//#include <glm/fwd.hpp>
//// Source file
//#include <glm/glm.hpp>
//// Include GLM core features
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//#include <glm/mat4x4.hpp>
//// Include GLM extensions
//#include <glm/gtc/matrix_transform.hpp>
//glm::mat4 transform(
//	glm::vec2 const & Orientation,
//	glm::vec3 const & Translate,
//	glm::vec3 const & Up)
//{
//	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
//	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), Translate);
//	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
//	glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
//	glm::mat4 Model = glm::mat4(1.0f);
//	return Projection * View * Model;
//}



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

	//background
	GameObjects::BaseGameObject *background = new GameObjects::BaseGameObject();
	GameComponents::SpriteComponent *backSprite = new GameComponents::SpriteComponent(background, std::string("forest.png"), GameComponents::FILE_TYPE::PNG);
	background->attachComponent((GameComponents::BaseComponent *)backSprite);
	background->setX(0);
	background->setY(0);
	core.Add(background);

	//player
	GameObjects::BaseGameObject *mario = new GameObjects::BaseGameObject();

	GameComponents::InputComponent *inputComp = new GameComponents::InputComponent(mario);
	GameComponents::SpriteComponent *spriteComp = new GameComponents::SpriteComponent(mario, std::string("desc-megaman.json"), GameComponents::FILE_TYPE::JSON);
	GameComponents::BodyComponent *bodyComp = new GameComponents::BodyComponent(mario);

	mario->setX(150);
	mario->setY(400);
	mario->attachComponent((GameComponents::BaseComponent *)inputComp);
	mario->attachComponent((GameComponents::BaseComponent *)spriteComp);
	mario->attachComponent((GameComponents::BaseComponent *)bodyComp);

	core.Add(mario);

	//player 2 
	GameObjects::BaseGameObject *mario2 = new GameObjects::BaseGameObject();

	GameComponents::InputComponent *inputComp2 = new GameComponents::InputComponent(mario2);
	GameComponents::SpriteComponent *spriteComp2 = new GameComponents::SpriteComponent(mario2, std::string("desc-metalslug.json"), GameComponents::FILE_TYPE::JSON);
//	GameComponents::BodyComponent *bodyComp2 = new GameComponents::BodyComponent(mario2);

	mario2->setX(100);
	mario2->setY(100);
	//mario2->attachComponent((GameComponents::BaseComponent *)inputComp2);
	mario2->attachComponent((GameComponents::BaseComponent *)spriteComp2);
//	mario2->attachComponent((GameComponents::BaseComponent *)bodyComp2);

	core.Add(mario2);


	/*sf::Music music;
	if (!music.openFromFile("dr_wily_stage.ogg"))
		return -1;
	music.play();*/

	//start
	core.Init();
	core.MainLoop();


/*
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong. 
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return (1);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...
*/
    return (0);
}