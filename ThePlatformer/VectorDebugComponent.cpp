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
				this->velocity = ((VectorMessage *)message)->vector;
				break;
			case Message::SHOW_DEBUG:
				showDebug = !showDebug;
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
		float x = (float)this->composition->getX();
		float y = (float)this->composition->getY();
		float height = (float)this->composition->getHeight();
		float width = (float)this->composition->getWidth();
		float centerX = x + width / 2;
		float centerY = y + height / 2;

		// top
		if (showDebug)
		{
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
	}


	void VectorDebugComponent::Init()
	{
		velocity = glm::vec2(0, 0);
		showDebug = false;
	}

}