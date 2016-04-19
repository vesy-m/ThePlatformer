#include "SpriteComponent.h"
#include "debugManager.h"

namespace GameComponents {
	SpriteComponent::SpriteComponent(GameObjects::BaseGameObject *object, const std::string &fileName) : BaseComponent(object)
	{
		object->attachComponent(this);
		_fileName = fileName;
		revertX = false;
		revertY = false;
		currentFrame = 0;
		counter = 0;
		currentAnim = "default";
		rotateNum = -1;
		isDashing = false;
	}

	SpriteComponent::~SpriteComponent()
	{
	}

	void SpriteComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::LEFT_DASH:
			isDashing = true;
			if (std::string("dash").compare(currentAnim) != 0 || revertX != true) {
				currentFrame = 0;
				prevAnim = currentAnim;
				currentAnim = "dash";
				revertX = true;
			}
			if (revertX != true)
				revertX = true;
			break;
		case GameMessage::RIGHT_DASH:
			isDashing = true;
			if (std::string("dash").compare(currentAnim) != 0 || revertX != false) {
				currentFrame = 0;
				prevAnim = currentAnim;
				currentAnim = "dash";
				revertX = false;
			}
			if (revertX != false)
				revertX = false;
			break;
		case GameMessage::STOP_DASH:
			isDashing = false;
			if (std::string("dash").compare(currentAnim) == 0) {
				currentFrame = 0;
				currentAnim = prevAnim;
			}
			break;
		case GameMessage::BASEBALL_SHOOT:
			if (isDashing)
				break;
			if (std::string("shoot").compare(currentAnim) != 0) {
				currentFrame = 0;
				prevAnim = currentAnim;
				currentAnim = "shoot";
			}
			break;
		case GameMessage::BLOCK:
			isDashing = true;
			if (std::string("block").compare(currentAnim) != 0) {
				currentFrame = 0;
				prevAnim = currentAnim;
				currentAnim = "block";
			}
			break;
		case GameMessage::STOP_BLOCK:
			isDashing = false;
			if (std::string("default").compare(currentAnim) != 0) {
				currentFrame = 0;
				prevAnim = currentAnim;
				currentAnim = "default";
			}
			break;
		case GameMessage::LEFT:
			if (isDashing)
				break;
			if ((std::string("walk").compare(currentAnim) != 0 || revertX != true) && std::string("jump").compare(currentAnim) != 0 && std::string("shoot").compare(currentAnim) != 0) {
				currentFrame = 0;
				prevAnim = currentAnim;
				currentAnim = "walk";
				revertX = true;
			}
			if (revertX != true)
				revertX = true;
			break;
		case GameMessage::RIGHT:
			if (isDashing)
				break;
			if ((std::string("walk").compare(currentAnim) != 0 || revertX != false) && std::string("jump").compare(currentAnim) != 0 && std::string("shoot").compare(currentAnim) != 0) {
				currentFrame = 0;
				prevAnim = currentAnim;
				currentAnim = "walk";
				revertX = false;
			}
			if (revertX != false)
				revertX = false;
			break;
		case GameMessage::JUMP_ANIMATION:
		case GameMessage::JUMP:
			if (isDashing)
				break;
			if (std::string("jump").compare(currentAnim) != 0) {
				currentFrame = 0;
				currentAnim = "jump";
			}
			break;
		case GameMessage::STAND_ANIMATION:
			if (std::string("default").compare(currentAnim) != 0) {
				currentFrame = 0;
				currentAnim = "default";
			}
			break;
		case GameMessage::ROTATE_LEFT:
			GameTools::debugManager::getInstance().rotateNum = -1;
			break;
		case GameMessage::ROTATE_RIGHT:
			GameTools::debugManager::getInstance().rotateNum = 1;
			break;
		default:
			break;
		}
	}

	COMPONENT_TYPE SpriteComponent::getType() const
	{
		return this->type;
	}

	void SpriteComponent::Update(double)
	{
		float xmin = 0;
		float xmax = 1;
		float ymin = 0;
		float ymax = 1;
		GameTools::Texture *texture = sheet->getTexture();
		GLint width = texture->getWidth();
		GLint height = texture->getHeight();
		GLint posX = this->composition->getX() + (this->composition->getWidth() / 2);
		GLint posY = this->composition->getY() + (this->composition->getHeight() / 2);

		glEnable(GL_TEXTURE_2D);

		if (sheet->isAnimated()) {
			GameTools::SpriteAnimation anim = sheet->getAnim(this->currentAnim);

			// get height and width of the sprite of the currentFrame
			height = anim.getSpriteYmax(currentFrame) - anim.getSpriteYmin(currentFrame);
			width = anim.getSpriteXmax(currentFrame) - anim.getSpriteXmin(currentFrame);

			xmin = (float)(anim.getSpriteXmin(currentFrame)) / (float)texture->getWidth();
			xmax = (float)(anim.getSpriteXmax(currentFrame)) / (float)texture->getWidth();

			// Y axis must be inverted because the opengl Y axis go from bottom to top
			ymin = (float)(texture->getHeight() - anim.getSpriteYmax(currentFrame)) / (float)texture->getHeight();
			ymax = (float)(texture->getHeight() - anim.getSpriteYmin(currentFrame)) / (float)texture->getHeight();

			if (counter == anim.getTime() && (currentFrame + 1) == anim.getSizeListFrame() && anim.getIsRepeated() == false) {
				currentAnim = prevAnim;
				currentFrame = 0;
			}
			else if (counter > anim.getTime()) {
				counter = 0;
				currentFrame = (currentFrame + 1) % anim.getSizeListFrame();
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
		if (this->sheet->positionSprite == GameTools::SpriteSheet::BOTTOM_CENTER) {
			pointY = -height;
			pointYHeight = 0;
			posY = this->composition->getY() + this->composition->getHeight();
		}
		if (this->revertY) {
			pointY += height;
			pointYHeight -= height;
		}

		pointX = (int)(pointX * this->composition->getScale());
		pointXWidth = (int)(pointXWidth * this->composition->getScale());
		pointY = (int)(pointY * this->composition->getScale());
		pointYHeight = (int)(pointYHeight * this->composition->getScale());

		glTranslated(posX, posY, 0);
		glRotated(this->composition->getRotate(), 0, 0, 1);
		glBegin(GL_QUADS);
			glTexCoord2f(xmin, ymax); glVertex2i(pointX, pointY);
			glTexCoord2f(xmax, ymax); glVertex2i(pointXWidth, pointY);
			glTexCoord2f(xmax, ymin); glVertex2i(pointXWidth, pointYHeight);
			glTexCoord2f(xmin, ymin); glVertex2i(pointX, pointYHeight);
		glEnd();
		glRotatef((GLfloat)-this->composition->getRotate(), 0.0, 0.0, 1.0);
		glTranslated(-(posX), -(posY), 0);

		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	void SpriteComponent::Init()
	{
		this->sheet = new GameTools::SpriteSheet(this->_fileName);
		GameTools::Texture *texture = sheet->getTexture();
		GLint width = texture->getWidth();
		GLint height = texture->getHeight();
		if (this->composition->getWidth() == 0 && this->composition->getHeight() == 0) {
			this->composition->setWidth(width);
			this->composition->setHeight(height);
		}
	}
}