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
		resizeCamera();
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
				component->Update(dt);
			}
		}
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			std::vector<GameComponents::BaseComponent*> componentList = object->getComponents(GameComponents::COMPONENT_TYPE::DEBUGVECTOR);
			for each (GameComponents::BaseComponent* component in componentList)
			{
				component->Update(dt);
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

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(Camera::getInstance().cameraStartX, Camera::getInstance().cameraEndX, Camera::getInstance().cameraEndY, Camera::getInstance().cameraStartY, -1, 1);
		//glOrtho(426, 826, 720, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	}

	void GraphicsSystem::resizeCamera()
	{
		GLint iViewport[4];
		glGetIntegerv(GL_VIEWPORT, iViewport);
		int screenWidth = iViewport[0] + iViewport[2];
		int screenHeight = iViewport[1] + iViewport[3];

		int sizeWidthMax = screenWidth;
		int sizeToWidthMax = screenWidth - 300;
		int sizeWidthMin = screenWidth / 2;

		std::vector<GameObjects::BaseGameObject *> listPlayers = ObjectFactory::getInstance().getCurrentLevel().getPlayers();
		if (listPlayers.size() == 2) {
			int XmiddlePlayer1 = listPlayers[0]->getX() + (listPlayers[0]->getWidth() / 2);
			int XmiddlePlayer2 = listPlayers[1]->getX() + (listPlayers[1]->getWidth() / 2);
			int xMiddle = ((XmiddlePlayer1 < XmiddlePlayer2) ? XmiddlePlayer1 : XmiddlePlayer2) + (abs(XmiddlePlayer1 - XmiddlePlayer2) / 2);
			int yMiddle = ((listPlayers[0]->getY() < listPlayers[1]->getY()) ? listPlayers[0]->getY() : listPlayers[1]->getY()) + (abs(listPlayers[0]->getY() - listPlayers[1]->getY()) / 2);

			int newWidth = abs(listPlayers[0]->getX() - listPlayers[1]->getX()) + 300;
			int currentWidth = Camera::getInstance().cameraEndX - Camera::getInstance().cameraStartX;

			if (newWidth > sizeToWidthMax) {
				newWidth = sizeWidthMax;
			}
			if (newWidth > sizeToWidthMax && currentWidth < newWidth - 10) {
				newWidth = currentWidth + 10;
			}
			if (newWidth <= sizeToWidthMax && currentWidth > newWidth + 10) {
				newWidth = currentWidth - 10;
			}
			if (newWidth < sizeWidthMin) {
				newWidth = sizeWidthMin;
			}
			if (newWidth > sizeWidthMax) {
				newWidth = sizeWidthMax;
			}

			int height = newWidth * screenHeight / screenWidth;

			int newXCamera = xMiddle - newWidth / 2;
			int newYCamera = yMiddle - height / 2;

			//border top
			if (newXCamera < 0) {
				newXCamera = 0;
			}
			if (newYCamera < 0) {
				newYCamera = 0;
			}

			Camera::getInstance().cameraStartX = newXCamera;
			Camera::getInstance().setWidth(newWidth);
			Camera::getInstance().cameraStartY = newYCamera;
			Camera::getInstance().setHeight(height);

			//border bottom
			if (Camera::getInstance().cameraEndX > screenWidth) {
				Camera::getInstance().setX(Camera::getInstance().cameraStartX - (Camera::getInstance().cameraEndX - screenWidth));
			}
			if (Camera::getInstance().cameraEndY > screenHeight) {
				Camera::getInstance().setY(Camera::getInstance().cameraStartY - (Camera::getInstance().cameraEndY - screenHeight));
			}
		}

	}

	void GraphicsSystem::SendMessage()
	{
	}
}
