#include "VectorDebugComponent.h"

namespace GameComponents {

	VectorDebugComponent::VectorDebugComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
	}


	VectorDebugComponent::~VectorDebugComponent()
	{
	}

	void VectorDebugComponent::sendMessage(Message *message)
	{
		switch (message->id)
		{
			case Message::DEBUGVECTOR:
				this->velocity = ((vectorMessage *)message)->vector;
				break;
			default:
				break;
		}
	}

	COMPONENT_TYPE VectorDebugComponent::getType()
	{
		return this->type;
	}

	void VectorDebugComponent::Update()
	{
		int x = this->composition->getX();
		int y = this->composition->getY();
		int height = this->composition->getHeight();
		int width = this->composition->getWidth();
		int centerX = x + width / 2;
		int centerY = y + height / 2;

		// top
		glLineWidth(1);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x, y);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x + width, y);
		glEnd();
		
		//left
		glLineWidth(1);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x, y);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x, y + height);
		glEnd();

		//right
		glLineWidth(1);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x + width, y);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x + width, y + height);
		glEnd();

		//bottom
		glLineWidth(1);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x, y + height);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x + width, y + height);
		glEnd();

		//velocity
		glLineWidth(3);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(centerX, centerY);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(centerX + velocity.x, centerY + velocity.y);
		glEnd();
	}


	void VectorDebugComponent::Init()
	{
		velocity = glm::vec2(0, 0);
	}

}