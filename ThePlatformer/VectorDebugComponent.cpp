#include "VectorDebugComponent.h"

namespace GameComponents {

	VectorDebugComponent::VectorDebugComponent(GameObjects::BaseGameObject *object, std::string typeDraw) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->typeDraw = typeDraw;
	}

	VectorDebugComponent::~VectorDebugComponent()
	{
	}

	void VectorDebugComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::VELOCITY_VECTOR:
			this->velocity = ((GameMessage::VectorMessage *)message)->vector;
			break;
		default:
			break;
		}
	}

	COMPONENT_TYPE VectorDebugComponent::getType() const
	{
		return this->type;
	}

	void VectorDebugComponent::Update(double)
	{
		float x = (float)this->composition->getX();
		float y = (float)this->composition->getY();
		float height = (float)this->composition->getHeight();
		float width = (float)this->composition->getWidth();
		float centerX = x + width / 2;
		float centerY = y + height / 2;

		if (!GameTools::debugManager::getInstance().isActivateGraphic()) return;
		// top
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(1);
		if (typeDraw == "circle") {
			drawHollowCircle(centerX, centerY, height / 2);
		}
		else if (typeDraw == "square") {
			drawSquare(x, y, width, height);
		}
		//velocity
		glLineWidth(3);

		glBegin(GL_LINES);
			glVertex2f(centerX, centerY);
			glVertex2f(centerX + velocity.x, centerY + velocity.y);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
	}

	void VectorDebugComponent::drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
		int i;
		int lineAmount = 100; //# of triangles used to draw circle

							  //GLfloat radius = 0.8f; //radius
		GLfloat twicePi = 2.0f * glm::pi<float>();

		glBegin(GL_LINE_LOOP);
		for (i = 0; i <= lineAmount; i++) {
			glVertex2f(
				x + (radius * cos(i *  twicePi / lineAmount)),
				y + (radius* sin(i * twicePi / lineAmount))
				);
		}
		glEnd();
	}

	void VectorDebugComponent::drawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
		glBegin(GL_LINES);
			glVertex2f(x, y);
			glVertex2f(x + width, y);
			//left
			glVertex2f(x, y);
			glVertex2f(x, y + height);
			//right
			glVertex2f(x + width, y);
			glVertex2f(x + width, y + height);
			//bottom
			glVertex2f(x, y + height);
			glVertex2f(x + width, y + height);
		glEnd();
	}

	void VectorDebugComponent::Init()
	{
		velocity = glm::vec2(0, 0);
	}
}