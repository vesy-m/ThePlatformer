#include "FireBallComponent.h"
#include "Message.h"
#include "FireMessage.h"
#include "AimMessage.h"

#include <assert.h>

//#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
//#include <SFML\Window.hpp>
//#include <map>
//#include <sstream>
//#include "JSONParser.h"
//#include "BaseGameObject.h"
#include "GraphicsSystem.h"
#include "debugManager.h"
//#include "ObjectFactory.h"


namespace GameMessage {
	class Message;
	class FireMessage;
}

namespace GameComponents {
	FireBallComponent::FireBallComponent(GameObjects::BaseGameObject *object) : FireComponent(object) {
	}

	FireBallComponent::~FireBallComponent() {
	}

	void FireBallComponent::Init(void) {
	}

	void FireBallComponent::sendMessage(GameMessage::Message *message) {
		if (message->id == GameMessage::FIRE) {
			GameMessage::FireMessage *fireMessage = dynamic_cast<GameMessage::FireMessage*>(message);
			assert(fireMessage != NULL);

			GLint iViewport[4];
			glGetIntegerv(GL_VIEWPORT, iViewport);
			int screenWidth = iViewport[0] + iViewport[2];
			int screenHeight = iViewport[1] + iViewport[3];
			int resolutionWidth = GameSystems::GraphicsSystem::Camera::getInstance().resolutionWidth;
			int resolutionHeight = GameSystems::GraphicsSystem::Camera::getInstance().resolutionHeight;

			int cameraWith = GameSystems::GraphicsSystem::Camera::getInstance().cameraEndX - GameSystems::GraphicsSystem::Camera::getInstance().cameraStartX;
			int cameraHeight = GameSystems::GraphicsSystem::Camera::getInstance().cameraEndY - GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY;
			int mouseX = fireMessage->getEvent().mouseButton.x * cameraWith / screenWidth;
			int mouseY = fireMessage->getEvent().mouseButton.y * cameraHeight / screenHeight;

			mouseX += GameSystems::GraphicsSystem::Camera::getInstance().cameraStartX;
			mouseY += GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY;

			int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
			int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));

			glm::vec2 direction = glm::vec2(mouseX - centerX, mouseY - centerY);

			GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(getComposition(), getComposition()->getX(),
				getComposition()->getY(), fireMessage->getDuration(), glm::normalize(direction), GameSystems::ObjectFactory::SOCCER_BALL);
		}
	}
}