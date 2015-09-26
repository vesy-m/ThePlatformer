#include "SpriteComponent.h"

namespace GameComponents {
	SpriteComponent::SpriteComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
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
		/*
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// fov, aspect, near, far 
		gluPerspective(60, 1, 1, 10);
		gluLookAt(0, 0, -2, 
			0, 0, 2,
			0, 1, 0); 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(1, 1); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(1, 0); glVertex3f(0.0, 1.0, 0.0);
		glTexCoord2d(0, 0); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2d(0, 1); glVertex3f(1.0, 0.0, 0.0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopAttrib();

		glFlush();*/




		/*
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2i(0, ilGetInteger(IL_IMAGE_HEIGHT));
		glVertex2i(0, 0);
		glTexCoord2i(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));
		glVertex2i(ilGetInteger(IL_IMAGE_WIDTH), 0);
		glTexCoord2i(ilGetInteger(IL_IMAGE_WIDTH), 0);
		glVertex2i(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));
		glTexCoord2i(0, 0);
		glVertex2i(0, ilGetInteger(IL_IMAGE_HEIGHT));
		glEnd();
		glFlush();*/




		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
		glEnable(GL_TEXTURE_2D);

		GLint height = 50;
		GLint width = 50;

		GLint posX = this->composition->getX();
		GLint posY = this->composition->getY();

		if (posY > 600)
			this->composition->setY(0);

		if (prevX < posX) {
			glBegin(GL_QUADS);
				glTexCoord2i(0, 1);	glVertex2i(posX, posY);
				glTexCoord2i(1, 1); glVertex2i(posX + width, posY);
				glTexCoord2i(1, 0); glVertex2i(posX + width, posY + height);
				glTexCoord2i(0, 0);	glVertex2i(posX, posY + height);
			glEnd();
		}
		else {
			glBegin(GL_QUADS);
				glTexCoord2i(0, 1);	glVertex2i(posX + width, posY);
				glTexCoord2i(1, 1); glVertex2i(posX, posY);
				glTexCoord2i(1, 0); glVertex2i(posX, posY + height);
				glTexCoord2i(0, 0);	glVertex2i(posX + width, posY + height);
			glEnd();
		}

		prevX = posX;
	}

	void SpriteComponent::Init()
	{

		//GLenum err = glewInit();
		//if (GLEW_OK != err)
		//{
		//	std::cout << "fail glew" << std::endl;
		//}

		//glClearColor(0.0, 0.0, 0.0, 0.0);

		//GLint iViewport[4];

		//glGetIntegerv(GL_VIEWPORT, iViewport);
		//glMatrixMode(GL_PROJECTION);
		//glPushMatrix();
		//glLoadIdentity();
		//glOrtho(iViewport[0], iViewport[0] + iViewport[2], iViewport[1] + iViewport[3], iViewport[1], -1, 1);
		//glMatrixMode(GL_MODELVIEW);
		//glPushMatrix();
		//glLoadIdentity();

		//glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);

		//if (!glewIsSupported("GL_EXT_texture_rectangle"))
		//{

		//	printf("ERROR: Texture rectangles not supported on this video card!");

		//	Sleep(2000);

		//	exit(-1);

		//}
		//glDisable(GL_LIGHTING);
		//glDisable(GL_DITHER);
		//glDisable(GL_BLEND);
		//glDisable(GL_DEPTH_TEST);




		//WORK


		//glShadeModel(GL_SMOOTH);
		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		//glEnable(GL_DEPTH_TEST);
		//GLfloat tab1float[] = { 2.0, 2.0, 2.0, 0.0 };
		//GLfloat tab2float[] = { 1.0, 1.0, 1.0, 0.0 };
		//glLightfv(GL_LIGHT0, GL_POSITION, tab1float);
		//glLightfv(GL_LIGHT0, GL_AMBIENT, tab2float);


		//glm::mat4 projection = glm::ortho(0, 800, 600, 0);


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

		texture = loadTexture("mario.png");
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

		return texture;
	}
}