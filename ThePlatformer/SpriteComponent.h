#pragma once
#ifndef _SPRITECOMPONENT_H_
#define _SPRITECOMPONENT_H_

#include "BaseGameObject.h"

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <il.h>
#include <cstdio>
#include <string>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SpriteSheet.h"

#define TEXTURE_LOAD_ERROR 0

namespace GameComponents {
	enum FILE_TYPE
	{
		JSON,
		PNG
	};

	class SpriteComponent : BaseComponent
	{
	public:
		SpriteComponent(GameObjects::BaseGameObject *, std::string &fileName, FILE_TYPE fileType);
		~SpriteComponent();
		COMPONENT_TYPE getType();
		void Update();
		void Init();
		GLuint loadTexture(const std::string filename);
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::SPRITE;
		GLuint texture;
		SpriteSheet sheet;
		int prevX = 0;
		int currentFrame = 0;
		int counter = 0;
		std::string _fileName;
		FILE_TYPE _fileType;
		int _width;
		int _height;

	};
}

#endif // !_SPRITECOMPONENT_H_