#include "SpriteComponent.h"

namespace GameComponents {
	SpriteComponent::SpriteComponent(GameObjects::BaseGameObject *object, const std::string &fileName) : BaseComponent(object)
	{
		_fileName = fileName;
		revertX = false;
		revertY = false;
		currentFrame = 0;
		counter = 0;
		currentAnim = "default";
	}

	SpriteComponent::~SpriteComponent()
	{
	}

	void SpriteComponent::sendMessage(Message *message)
	{
		switch (message->id)
		{
			case Message::LEFT:
				if ((std::string("walk").compare(currentAnim) != 0 || revertX != true) && std::string("jump").compare(currentAnim) != 0) {
					currentFrame = 0;
					currentAnim = "walk";
					revertX = true;
				}
				if (revertX != true)
				{
					revertX = true;
				}
				break;
			case Message::RIGHT:
				if ((std::string("walk").compare(currentAnim) != 0 || revertX != false) && std::string("jump").compare(currentAnim) != 0) {
					currentFrame = 0;
					currentAnim = "walk";
					revertX = false;
				}
				if (revertX != false)
				{
					revertX = false;
				}
				break;
			case Message::JUMP_ANIMATION:
			case Message::JUMP:
				if (std::string("jump").compare(currentAnim) != 0) {
					currentFrame = 0;
					currentAnim = "jump";
				}
				break;
			case Message::STAND_ANIMATION:
				if (std::string("default").compare(currentAnim) != 0) {
					currentFrame = 0;
					currentAnim = "default";
				}
				break;
			default:
				break;
		}
	}

	COMPONENT_TYPE SpriteComponent::getType()
	{
		return this->type;
	}

	void SpriteComponent::Update()
	{
		float xmin = 0;
		float xmax = 1;
		float ymin = 0;
		float ymax = 1;
		Texture *texture = sheet->getTexture();
		GLint width = texture->getWidth();
		GLint height = texture->getHeight();
		GLint posX = this->composition->getX() + (this->composition->getWidth() / 2);
		GLint posY = this->composition->getY() + (this->composition->getHeight() / 2);

		if (!std::string("sun").compare(this->composition->getName())) {
			this->composition->setRotate((this->composition->getRotate() + 1) % 360);
		}

		glEnable(GL_TEXTURE_2D);

		if (sheet->isAnimated()) {
			SpriteAnimation anim = sheet->getAnim(this->currentAnim);

			// get height and width of the sprite of the currentFrame
			height = anim.getSpriteYmax(currentFrame) - anim.getSpriteYmin(currentFrame);
			width = anim.getSpriteXmax(currentFrame) - anim.getSpriteXmin(currentFrame);
				
			xmin = (float)(anim.getSpriteXmin(currentFrame)) / (float)texture->getWidth();
			xmax = (float)(anim.getSpriteXmax(currentFrame)) / (float)texture->getWidth();

			// Y axis must be inverted because the opengl Y axis go from bottom to top
			ymin = (float)(texture->getHeight() - anim.getSpriteYmax(currentFrame)) / (float)texture->getHeight();
			ymax = (float)(texture->getHeight() - anim.getSpriteYmin(currentFrame)) / (float)texture->getHeight();

			if (counter > anim.getTime()) {
				currentFrame = (currentFrame + 1) % anim.getSizeListFrame();
				counter = 0;
			}
			counter++;
		}
		glBindTexture(GL_TEXTURE_2D, texture->getId());

		int pointX = -(width / 2);
		int pointXWidth = (width / 2);
		if (this->revertX) {
			pointX += width;
			pointXWidth -= width;
		}
		int pointY = -(height / 2);
		int pointYHeight = (height / 2);
		if (this->revertY) {
			pointY += height;
			pointYHeight -= height;
		}

		pointX *= this->composition->getScale();
		pointXWidth *= this->composition->getScale();
		pointY *= this->composition->getScale();
		pointYHeight *= this->composition->getScale();

		glTranslated(posX, posY, 0);
		glRotated(this->composition->getRotate(), 0, 0, 1);
		glBegin(GL_QUADS);
			glTexCoord2f(xmin, ymax); glVertex2i(pointX, pointY);
			glTexCoord2f(xmax, ymax); glVertex2i(pointXWidth, pointY);
			glTexCoord2f(xmax, ymin); glVertex2i(pointXWidth, pointYHeight);
			glTexCoord2f(xmin, ymin); glVertex2i(pointX, pointYHeight);
		glEnd();
		glRotatef(-this->composition->getRotate(), 0, 0, 1);
		glTranslated(-posX, -posY, 0);

		glDisable(GL_TEXTURE_2D);
	}

	void SpriteComponent::Init()
	{
		this->sheet = new SpriteSheet(this->_fileName);
		Texture *texture = sheet->getTexture();
		GLint width = texture->getWidth();
		GLint height = texture->getHeight();
		if (this->composition->getWidth() == 0 && this->composition->getHeight() == 0) {
			this->composition->setWidth(width);
			this->composition->setHeight(height);
		}
	}
}