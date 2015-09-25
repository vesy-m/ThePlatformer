#include "SpriteComponent.h"

namespace GameComponents {
	SpriteComponent::SpriteComponent()
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
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		/* fov, aspect, near, far */
		gluPerspective(60, 1, 1, 10);
		gluLookAt(0, 0, -2, /* eye */
			0, 0, 2, /* center */
			0, 1, 0); /* up */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		/* create a square on the XY
		note that OpenGL origin is at the lower left
		but texture origin is at upper left
		=> it has to be mirrored
		(gasman knows why i have to mirror X as well) */
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2d(1, 1); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(1, 0); glVertex3f(0.0, 1.0, 0.0);
		glTexCoord2d(0, 0); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2d(0, 1); glVertex3f(1.0, 0.0, 0.0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopAttrib();

		glFlush();
	}

	void SpriteComponent::Init()
	{

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_SMOOTH);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		GLfloat tab1float[] = { 2.0, 2.0, 2.0, 0.0 };
		GLfloat tab2float[] = { 1.0, 1.0, 1.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, tab1float);
		glLightfv(GL_LIGHT0, GL_AMBIENT, tab2float);

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