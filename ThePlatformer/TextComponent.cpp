#include "TextComponent.h"

namespace GameComponents {

	TextComponent::TextComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
	}


	TextComponent::~TextComponent()
	{
	}

	COMPONENT_TYPE TextComponent::getType()
	{
		return this->type;
	}

	void TextComponent::Update() {

	}

	void TextComponent::Update(double dt)
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

		if (dt == 0.0 || debugManager::getInstance().isActivateGraphic() == false) {
			return;
		}

		glEnable(GL_TEXTURE_2D);

		int fps = (int)(1000.0 / dt);
		std::stringstream ss = std::stringstream();
		ss << fps;
		std::string text = std::string("FPS : " + ss.str());

		glBindTexture(GL_TEXTURE_2D, texture->getId());
		for (size_t i = 0; i < text.size(); i++) {

			std::string strChar(1, text.at(i));
			SpriteAnimation anim = sheet->getAnim(strChar);

			// get height and width of the sprite of the currentFrame
			height = anim.getSpriteYmax(0) - anim.getSpriteYmin(0);
			width = anim.getSpriteXmax(0) - anim.getSpriteXmin(0);

			height /= 15;
			width /= 15;

			xmin = (float)(anim.getSpriteXmin(0)) / (float)texture->getWidth();
			xmax = (float)(anim.getSpriteXmax(0)) / (float)texture->getWidth();

			// Y axis must be inverted because the opengl Y axis go from bottom to top
			ymin = (float)(texture->getHeight() - anim.getSpriteYmax(0)) / (float)texture->getHeight();
			ymax = (float)(texture->getHeight() - anim.getSpriteYmin(0)) / (float)texture->getHeight();


			int pointX = posX;
			int pointXWidth = posX + width;
			int pointY = posY;
			int pointYHeight = posY + height;


			glBegin(GL_QUADS);
				glTexCoord2f(xmin, ymax); glVertex2i(pointX, pointY);
				glTexCoord2f(xmax, ymax); glVertex2i(pointXWidth, pointY);
				glTexCoord2f(xmax, ymin); glVertex2i(pointXWidth, pointYHeight);
				glTexCoord2f(xmin, ymin); glVertex2i(pointX, pointYHeight);
			glEnd();
			posX += width;
		}

		glDisable(GL_TEXTURE_2D);
	}

	void TextComponent::Init()
	{
		this->sheet = new SpriteSheet("font.json");
	}

	void TextComponent::sendMessage(Message *)
	{
	}

}