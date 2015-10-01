#include "SpriteComponent.h"

namespace GameComponents {
	SpriteComponent::SpriteComponent(GameObjects::BaseGameObject *object, std::string &fileName) : BaseComponent(object)
	{
		_fileName = fileName;
		revertX = false;
		revertY = false;
		currentFrame = 0;
		counter = 0;
		currentAnim = "walk";
	}

	SpriteComponent::~SpriteComponent()
	{
	}

	void SpriteComponent::sendMessage(Message *message)
	{
		switch (message->id)
		{
			case Message::LEFT:
				revertX = true;
				break;
			case Message::RIGHT:
				revertX = false;
				break;
			case Message::JUMP:
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
		GLint posX = this->composition->getX();
		GLint posY = this->composition->getY();
		Texture *texture = sheet->getTexture();
		GLint width = texture->getWidth();
		GLint height = texture->getHeight();

		if (sheet->isAnimated()) {
			SpriteAnimation anim = sheet->getAnim(this->currentAnim);

			// get height and width of the sprite of the currentFrame
			height = anim.getSpriteYmax(currentFrame) - anim.getSpriteYmin(currentFrame);
			width = anim.getSpriteXmax(currentFrame) - anim.getSpriteXmin(currentFrame);

			// center the x position
			posX = this->composition->getX() - (width / 2);
			posY = this->composition->getY();
				
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

		
		int pointX = posX;
		int pointXWidth = posX + width;
		if (this->revertX) {
			pointX += width;
			pointXWidth -= width;
		}
		int pointY = posY;
		int pointYHeight = posY + height;
		if (this->revertY) {
			pointY += height;
			pointYHeight -= height;
		}

		glBegin(GL_QUADS);
			glTexCoord2f(xmin, ymax); glVertex2i(pointX, pointY);
			glTexCoord2f(xmax, ymax); glVertex2i(pointXWidth, pointY);
			glTexCoord2f(xmax, ymin); glVertex2i(pointXWidth, pointYHeight);
			glTexCoord2f(xmin, ymin); glVertex2i(pointX, pointYHeight);
		glEnd();
	}

	void SpriteComponent::Init()
	{
		viewportReload();

		this->sheet = new SpriteSheet(this->_fileName);
	}

	void SpriteComponent::viewportReload() {
		GLint iViewport[4];

		glGetIntegerv(GL_VIEWPORT, iViewport);
		std::cout << iViewport[0] << " " << iViewport[0] + iViewport[2] << " " << iViewport[1] + iViewport[3] << " " << iViewport[1] << std::endl;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(iViewport[0], iViewport[0] + iViewport[2], iViewport[1] + iViewport[3], iViewport[1], -1, 1);
		glPushMatrix();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
	}
}