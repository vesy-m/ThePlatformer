#include "AimComponent.h"


namespace GameComponents {
	AimComponent::AimComponent(GameObjects::BaseGameObject *object, const std::string &fileName) : BaseComponent(object)
	{
		object->attachComponent(this);
		_fileName = fileName;
		direction = glm::vec2(0, 0);
	}


	AimComponent::~AimComponent()
	{
	}

	void AimComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::AIM:
			GameMessage::AimMessage *aimMessage = dynamic_cast<GameMessage::AimMessage*>(message);
			
			direction = aimMessage->drawPoint;
			//std::cout << "Test" << std::endl;
			break;
		}
	}

	COMPONENT_TYPE AimComponent::getType()
	{
		return GameComponents::SPRITE;
	}

	void AimComponent::Update(double)
	{
		float xmin = 0;
		float xmax = 1;
		float ymin = 0;
		float ymax = 1;
		GameTools::Texture *texture = sheet->getTexture();
		GLint width = texture->getWidth();
		GLint height = texture->getHeight();

		glm::vec2 pointP = glm::vec2(this->getComposition()->getX() + (this->getComposition()->getHeight() / 2),
									 this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));

		float x = ((70 * direction.x) + pointP.x);
		float y = ((70 * direction.y) + pointP.y);
		glm::vec2 vector = glm::vec2(x, y);

		GLint posX = (int)vector.x;
		GLint posY = (int)vector.y;

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texture->getId());

		int pointX = -(width / 2);
		int pointXWidth = (width / 2);
		int pointY = -(height / 2);
		int pointYHeight = (height / 2);

		glTranslated(posX, posY, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(xmin, ymax); glVertex2i(pointX, pointY);
		glTexCoord2f(xmax, ymax); glVertex2i(pointXWidth, pointY);
		glTexCoord2f(xmax, ymin); glVertex2i(pointXWidth, pointYHeight);
		glTexCoord2f(xmin, ymin); glVertex2i(pointX, pointYHeight);
		glEnd();
		glTranslated(-(posX), -(posY), 0);

		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	void AimComponent::Init()
	{
		this->sheet = new GameTools::SpriteSheet(this->_fileName);
		GameTools::Texture *texture = sheet->getTexture();
	}
}
