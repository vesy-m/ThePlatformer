#include <SFML/Window.hpp>
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
	GameSystems::WindowInputSytem *winInput = new GameSystems::WindowInputSytem();

	GameObjects::BaseGameObject *mario = new GameObjects::BaseGameObject();

	GameComponents::InputComponent *inputComp = new GameComponents::InputComponent(mario);
	mario->attachComponent((GameComponents::BaseComponent *)inputComp);

	GameSystems::GraphicsSystem *graphics = new GameSystems::GraphicsSystem();

	GameComponents::SpriteComponent *spriteComp = new GameComponents::SpriteComponent(mario);
	mario->attachComponent((GameComponents::BaseComponent *)spriteComp);

	GameSystems::PhysicsSystem *physics = new GameSystems::PhysicsSystem();

	GameComponents::BodyComponent *bodyComp = new GameComponents::BodyComponent(mario);
	mario->attachComponent((GameComponents::BaseComponent *)bodyComp);

	core.Add(mario);
	core.Add((GameSystems::System *)winInput);
	core.Add((GameSystems::System *)physics);
	core.Add((GameSystems::System *)graphics);
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