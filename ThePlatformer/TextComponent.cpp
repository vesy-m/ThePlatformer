#include "TextComponent.h"
#include "GraphicsSystem.h"

namespace GameComponents {

	TextComponent::TextComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
	}

	TextComponent::~TextComponent()
	{
	}

	COMPONENT_TYPE TextComponent::getType() const
	{
		return this->type;
	}

	void TextComponent::Update() {
	}

	void TextComponent::Update(double dt)
	{
		if (this->composition->getType() == GameObjects::objectType::PLAYER)
		{
			int playerId = GameSystems::ObjectFactory::getInstance().getPlayerId(this->composition) + 1;
			std::string lifeText = "0";
			if (this->composition->getLife() >= 0)
				lifeText = std::to_string(this->composition->getLife());

			std::stringstream playerstr = std::stringstream();
			playerstr << "Player " << playerId;

			int posX = this->composition->getX() - 10;
			int posY = this->composition->getY() - 20;
			drawText(playerstr.str(), posX, posY, -5);
			playerstr << " : " << lifeText;
			if (playerId == 1) {
				posX = GameSystems::GraphicsSystem::Camera::getInstance().cameraStartX + 20;
				posY = GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY + 20;
			}
			else if (playerId == 2) {
				posX = GameSystems::GraphicsSystem::Camera::getInstance().cameraStartX + 320;
				posY = GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY + 20;
			}
			else if (playerId == 3) {
				posX = GameSystems::GraphicsSystem::Camera::getInstance().cameraEndX - 520;
				posY = GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY + 20;
			}
			else if (playerId == 4) {
				posX = GameSystems::GraphicsSystem::Camera::getInstance().cameraEndX - 220;
				posY = GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY + 20;
			}
			drawText(playerstr.str(), posX, posY, 1);
		}
		else if (GameSystems::ObjectFactory::getInstance().stateGame == GameSystems::ObjectFactory::gameState::MENU) {
			int posX = this->composition->getX();
			int posY = this->composition->getY();

			int playerId = GameSystems::ObjectFactory::getInstance().idWinPlayer + 1;
			std::stringstream playerstr = std::stringstream();
			playerstr << "Player " << playerId;
			drawText(playerstr.str(), posX, posY, 3);
		}
		else if (dt != 0.0 && GameTools::debugManager::getInstance().isActivateGraphic()) {
			int posX = GameSystems::GraphicsSystem::Camera::getInstance().cameraStartX + 20;
			int posY = GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY + 50;

			static int time_to_display = 1000;
			static int old_fps = 60;

			time_to_display -= (int)dt;
			if (time_to_display <= 0) {
				time_to_display = 1000;
				old_fps = (int)(1000.0 / dt);
			}

			std::stringstream fpsStr = std::stringstream();
			fpsStr << "FPS : " << old_fps;
			drawText(fpsStr.str(), posX, posY);
		}
	}

	void TextComponent::drawText(std::string str, int posX, int posY, int size) {
		GameTools::Texture *texture = sheet->getTexture();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->getId());
		for (size_t i = 0; i < str.size(); i++) {

			std::string strChar(1, str.at(i));
			GameTools::SpriteAnimation anim = sheet->getAnim(strChar);

			//get letter coordinate in texture 
			float xTexCoordMin = (float)(anim.getSpriteXmin(0)) / (float)texture->getWidth();
			float xTexCoordMax = (float)(anim.getSpriteXmax(0)) / (float)texture->getWidth();
			// Y axis must be inverted because the opengl Y axis go from bottom to top
			float yTexCoordMin = (float)(texture->getHeight() - anim.getSpriteYmax(0)) / (float)texture->getHeight();
			float yTexCoordMax = (float)(texture->getHeight() - anim.getSpriteYmin(0)) / (float)texture->getHeight();

			// get height and width of the sprite of the currentFrame
			GLint letterHeight = anim.getSpriteYmax(0) - anim.getSpriteYmin(0);
			GLint letterWidth = anim.getSpriteXmax(0) - anim.getSpriteXmin(0);

			letterHeight /= 20 - size;
			letterWidth /= 20 - size;

			int pointX = posX;
			int pointXWidth = posX + letterWidth;
			int pointY = posY;
			int pointYHeight = posY + letterHeight;

			glBegin(GL_QUADS);
				glTexCoord2f(xTexCoordMin, yTexCoordMax); glVertex2i(pointX, pointY);
				glTexCoord2f(xTexCoordMax, yTexCoordMax); glVertex2i(pointXWidth, pointY);
				glTexCoord2f(xTexCoordMax, yTexCoordMin); glVertex2i(pointXWidth, pointYHeight);
				glTexCoord2f(xTexCoordMin, yTexCoordMin); glVertex2i(pointX, pointYHeight);
			glEnd();
			posX += letterWidth;
		}

		glDisable(GL_TEXTURE_2D);
	}

	void TextComponent::Init()
	{
		this->sheet = new GameTools::SpriteSheet("./config/sprite_sheets/font.json");
	}

	void TextComponent::sendMessage(GameMessage::Message*)
	{
	}
}