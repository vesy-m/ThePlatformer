#include "SpriteComponent.h"

namespace GameComponents {
	SpriteComponent::SpriteComponent(GameObjects::BaseGameObject *object, std::string &fileName, FILE_TYPE fileType) : BaseComponent(object)
	{
		_fileName = fileName;
		_fileType = fileType;
	}

	SpriteComponent::~SpriteComponent()
	{
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
		GLint width = 50;
		GLint height = 50;


		if (_fileType == FILE_TYPE::JSON) {

			SpriteAnimation anim = sheet.anims["walk"];

			height = anim.listFrame[currentFrame][3] - anim.listFrame[currentFrame][2];
			width = anim.listFrame[currentFrame][1] - anim.listFrame[currentFrame][0];
			//width *= 4;
			//height *= 4;

			posX = this->composition->getX() - (width / 2);
			posY = this->composition->getY();
			//std::cout << anim.listFrame[currentFrame][0] << std::endl;
			xmin = (float)(anim.listFrame[currentFrame][0]) / (float)sheet.texture->getWidth();
			xmax = (float)(anim.listFrame[currentFrame][1]) / (float)sheet.texture->getWidth();
			ymin = (float)(sheet.texture->getHeight() - anim.listFrame[currentFrame][3]) / (float)sheet.texture->getHeight();
			ymax = (float)(sheet.texture->getHeight() - anim.listFrame[currentFrame][2]) / (float)sheet.texture->getHeight();
			//std::cout << xmin << " " << xmax << " " << ymin << " " << ymax << std::endl;
			//if (prevX < posX) {
			if (counter > anim.time) {
				currentFrame = (currentFrame + 1) % anim.listFrame.size();
				counter = 0;
			}
			glBindTexture(GL_TEXTURE_2D, sheet.texture->getId());
		}
		else {
			width = _width;
			height = _height;
			glBindTexture(GL_TEXTURE_2D, texture);
		}

		glBegin(GL_QUADS);
			glTexCoord2f(xmin, ymax); glVertex2i(posX, posY);
			glTexCoord2f(xmax, ymax); glVertex2i(posX + width, posY);
			glTexCoord2f(xmax, ymin); glVertex2i(posX + width, posY + height);
			glTexCoord2f(xmin, ymin); glVertex2i(posX, posY + height);
		glEnd();
		//}
		//else {
		//	glBegin(GL_QUADS);
		//		glTexCoord2i(0, 1);	glVertex2i(posX + width, posY);
		//		glTexCoord2i(1, 1); glVertex2i(posX, posY);
		//		glTexCoord2i(1, 0); glVertex2i(posX, posY + height);
		//		glTexCoord2i(0, 0);	glVertex2i(posX + width, posY + height);
		//	glEnd();
		//}
		if (_fileType == FILE_TYPE::JSON) {
			prevX = posX;
			counter++;
		}
	}

	void SpriteComponent::Init()
	{
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

		if (_fileType == FILE_TYPE::JSON) {
			std::string fileName = std::string(_fileName);
			sheet = SpriteSheet(fileName);
		}
		else {
			texture = loadTexture(_fileName);
		}
	}

	void SpriteComponent::sendMessage(Message *message)
	{
	}

	GLuint SpriteComponent::loadTexture(const std::string filename)
	{
		ILboolean success;
		unsigned int imageID;

		// init DevIL. This needs to be done only once per application
		ilInit();
		// generate an image name
		ilGenImages(1, &imageID);
		// bind it
		ilBindImage(imageID);
		// match image origin to OpenGL’s
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		// load  the image
		success = ilLoadImage((ILstring)filename.c_str());
		// check to see if everything went OK
		if (!success) {
			std::cout << "file charged" << std::endl;
		}
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);


		/* Create and load textures to OpenGL */
		glGenTextures(1, &texture); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT),
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			ilGetData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		_width = ilGetInteger(IL_IMAGE_WIDTH);
		_height = ilGetInteger(IL_IMAGE_HEIGHT);
		return texture;
	}
}