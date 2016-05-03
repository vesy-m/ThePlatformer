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
		GameTools::Texture *texture = sheet->getTexture();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->getId());
		if (this->composition->getType() == GameObjects::objectType::PLAYER || this->composition->getType() == GameObjects::objectType::PLAYER_ATTACK)
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
			switch (playerId - 1)
			{
			case 0:
				glColor3f(1.0, 0.0, 0.0);
				break;
			case 1:
				glColor3f(1.0, 1.0, 0.0);
				break;
			case 2:
				glColor3f(0.0, 1.0, 0.0);
				break;
			case 3:
				glColor3f(0.0, 0.0, 1.0);
				break;
			default:
				break;
			}
			drawText(playerstr.str(), posX, posY, 3);
			glColor3f(1.0, 1.0, 1.0);
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
			fpsStr << "FPS : " << (int)(1000.0 / dt);
			drawText(fpsStr.str(), posX, posY);
		}
		glDisable(GL_TEXTURE_2D);
	}

	void TextComponent::drawText(std::string str, int posX, int posY, int size) {
		int letterHeight, letterWidth;
		size_t sizeStr = str.size();
		glBegin(GL_QUADS);
		for (size_t i = 0; i < sizeStr; i++) {

			GameTools::SpriteSheet::Letter let = sheet->getLetter(str.at(i));

			letterHeight = let.height / (20 - size);
			letterWidth = let.width / (20 - size);

			glTexCoord2f(let.xTexCoordMin, let.yTexCoordMax); glVertex2i(posX, posY);
			glTexCoord2f(let.xTexCoordMax, let.yTexCoordMax); glVertex2i(posX + letterWidth, posY);
			glTexCoord2f(let.xTexCoordMax, let.yTexCoordMin); glVertex2i(posX + letterWidth, posY + letterHeight);
			glTexCoord2f(let.xTexCoordMin, let.yTexCoordMin); glVertex2i(posX, posY + letterHeight);
			posX += letterWidth;

		}
		glEnd();
	}

	void TextComponent::Init()
	{
		this->sheet = new GameTools::SpriteSheet("./config/sprite_sheets/font.json");
	}

	void TextComponent::sendMessage(GameMessage::Message*)
	{
	}
}