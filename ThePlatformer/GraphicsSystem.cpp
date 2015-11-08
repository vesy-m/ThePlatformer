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
		glColor3f((GLfloat)(1.0 / 255.0 * 104.0), (GLfloat)(1.0 / 255.0 * 185.0), (GLfloat)(1.0 / 255.0 * 228.0));
		glBegin(GL_QUADS);
			glVertex2i(0, 0);
			glVertex2i(0, Camera::getInstance().resolutionHeight);
			glVertex2i(Camera::getInstance().resolutionWidth, Camera::getInstance().resolutionHeight);
			glVertex2i(Camera::getInstance().resolutionWidth, 0);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent*component = object->getComponent(GameComponents::COMPONENT_TYPE::SPRITE);
			if (component) component->Update(dt);
		}
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent* component = object->getComponent(GameComponents::COMPONENT_TYPE::DEBUGVECTOR);
			if (component) component->Update(dt);
		}
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent* component = object->getComponent(GameComponents::COMPONENT_TYPE::TEXT);
			if (component) component->Update(dt);
		}
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		return 0;
	}

	void GraphicsSystem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		Camera::getInstance();
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent* component = object->getComponent(GameComponents::COMPONENT_TYPE::SPRITE);
			if (component) component->Init();
		}
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent* component = object->getComponent(GameComponents::COMPONENT_TYPE::DEBUGVECTOR);
			if (component) component->Init();
		}
		for each (GameObjects::BaseGameObject* object in listObjects)
		{
			GameComponents::BaseComponent* component = object->getComponent(GameComponents::COMPONENT_TYPE::TEXT);
			if (component) component->Init();
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
		int screenWidth = Camera::getInstance().resolutionWidth;//iViewport[0] + iViewport[2];
		int screenHeight = Camera::getInstance().resolutionHeight;//iViewport[1] + iViewport[3];

		int sizeWidthMax = screenWidth;
		int sizeToWidthMax = screenWidth - 300;
		int sizeWidthMin = (int)(screenWidth / 1.2);

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

	void GraphicsSystem::Camera::setX(int x)
	{
		int width = this->cameraEndX - this->cameraStartX;
		this->cameraStartX = x;
		this->cameraEndX = this->cameraStartX + width;
	}

	void GraphicsSystem::Camera::setY(int y)
	{
		int height = this->cameraEndY - this->cameraStartY;
		this->cameraStartY = y;
		this->cameraEndY = this->cameraStartY + height;
	}

	void GraphicsSystem::Camera::setWidth(int width)
	{
		this->cameraEndX = this->cameraStartX + width;
	}

	void GraphicsSystem::Camera::setHeight(int height)
	{
		this->cameraEndY = this->cameraStartY + height;
	}

	void GraphicsSystem::Camera::setResolution720p() {
		this->resolutionWidth = 1280;
		this->resolutionHeight = 720;
	}

	void GraphicsSystem::Camera::setResolution1080p() {
		this->resolutionWidth = 1920;
		this->resolutionHeight = 1080;
	}

	GraphicsSystem::Camera::Camera()
	{
		this->resolutionWidth = 1280;
		this->resolutionHeight = 720;
		this->cameraStartX = 0;
		this->cameraEndX = this->resolutionWidth;
		this->cameraStartY = 0;
		this->cameraEndY = this->resolutionHeight;
	}

	GraphicsSystem::Camera::~Camera()
	{
	}
}
