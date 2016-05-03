#include "LifeBarComponent.h"

namespace GameComponents {

	LifeBarComponent::LifeBarComponent(GameObjects::BaseGameObject *object, int color) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->life = 0;
		this->lifeMax = 200;
		this->widthLifeBar = 50;
		this->heightLifeBar = 6;
		switch (color)
		{
		case 0:
			this->barColor = glm::vec3(1.0, 0.0, 0.0);
			break;
		case 1:
			this->barColor = glm::vec3(1.0, 1.0, 0.0);
			break;
		case 2:
			this->barColor = glm::vec3(0.0, 1.0, 0.0);
			break;
		case 3:
			this->barColor = glm::vec3(0.0, 0.0, 1.0);
			break;
		default:
			break;
		}
	}

	LifeBarComponent::~LifeBarComponent()
	{
	}

	void LifeBarComponent::sendMessage(GameMessage::Message *message)
	{

	}

	COMPONENT_TYPE LifeBarComponent::getType() const
	{
		return this->type;
	}

	void LifeBarComponent::Update(double)
	{
		if (this->composition->getLife() >= 0)
			this->life = this->composition->getLife();
		this->drawSquare(this->composition->getX() + this->composition->getWidth() / 2, this->composition->getY() - 20, this->widthLifeBar / 2, this->heightLifeBar / 2, (int)(this->widthLifeBar * this->life / this->lifeMax));
	}

	void LifeBarComponent::drawSquare(int x, int y, int width, int height, int percent) {
		glBegin(GL_QUADS);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(x - width - 1, y - height - 1);
			glVertex2i(x - width - 1, y + height + 1);
			glVertex2i(x + width + 1, y + height + 1);
			glVertex2i(x + width + 1, y - height - 1);
			//life
			glColor3f(this->barColor.x, this->barColor.y, this->barColor.z);
			glVertex2i(x - width, y - height);
			glVertex2i(x - width, y + height);
			glVertex2i(x - width + percent, y + height);
			glVertex2i(x - width + percent, y - height);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
	}

	void LifeBarComponent::Init()
	{
		this->widthLifeBar = this->composition->getWidth();
	}
}