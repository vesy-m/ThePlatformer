#include "GraphicsSystem.h"
#include "TextComponent.h"

namespace GameSystems {
	GraphicsSystem::GraphicsSystem()
	{
	}


	GraphicsSystem::~GraphicsSystem()
	{
	}

	int GraphicsSystem::Update(double dt, std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		viewportReload();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		GLint iViewport[4];
		glGetIntegerv(GL_VIEWPORT, iViewport);
		glColor3f((GLfloat)(1.0 / 255.0 * 104.0), (GLfloat)(1.0 / 255.0 * 185.0), (GLfloat)(1.0 / 255.0 * 228.0));
		glBegin(GL_QUADS);
			glVertex2i(iViewport[0], iViewport[1]);
			glVertex2i(iViewport[0], iViewport[1] + iViewport[3]);
			glVertex2i(iViewport[0] + iViewport[2], iViewport[1] + iViewport[3]);
			glVertex2i(iViewport[0] + iViewport[2], iViewport[1]);
		glEnd();
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
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::TEXT);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				((GameComponents::TextComponent*)component)->Update(dt);
			}
		}
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		return 0;
	}

	void GraphicsSystem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		//viewportReload();
		GLint iViewport[4];
		glGetIntegerv(GL_VIEWPORT, iViewport);
		Camera::getInstance().cameraStartX = iViewport[0];
		Camera::getInstance().cameraEndX = iViewport[0] + iViewport[2];
		Camera::getInstance().cameraStartY = iViewport[1];
		Camera::getInstance().cameraEndY = iViewport[1] + iViewport[3];
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
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::TEXT);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Init();
			}
		}
	}

	void GraphicsSystem::viewportReload() {
		/*GLint iViewport[4];
		glGetIntegerv(GL_VIEWPORT, iViewport);
		int screenWidth = iViewport[0] + iViewport[2];
		int screenHeight = iViewport[1] + iViewport[3];
		int widthCamera = screenWidth / GameSystems::ObjectFactory::getInstance().getCurrentLevel().getScale();
		int heightCamera = screenHeight / GameSystems::ObjectFactory::getInstance().getCurrentLevel().getScale();


		//cameraStartX = (screenWidth / 2.0f) - (widthCamera / 2.0f);
		cameraEndX = cameraStartX + widthCamera;
		//cameraStartY = (screenHeight / 2.0f) - (heightCamera / 2.0f);
		cameraEndY = cameraStartY + heightCamera;
		*/
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(Camera::getInstance().cameraStartX, Camera::getInstance().cameraEndX, Camera::getInstance().cameraEndY, Camera::getInstance().cameraStartY, -1, 1);
		//glOrtho(426, 826, 720, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	}

	void GraphicsSystem::SendMessage()
	{
	}
}
