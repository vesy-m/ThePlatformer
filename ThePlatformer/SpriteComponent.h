#pragma once
#ifndef _SPRITECOMPONENT_H_
#define _SPRITECOMPONENT_H_

#include "BaseGameObject.h"

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <il.h>
#include <cstdio>
#include <string>

#define TEXTURE_LOAD_ERROR 0

namespace GameComponents {
	class SpriteComponent : BaseComponent
	{
	public:
		SpriteComponent();
		~SpriteComponent();
		COMPONENT_TYPE getType();
		void Update();
		void Init();
		GLuint loadTexture(const std::string filename);
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::SPRITE;
		GLuint texture;
	};
}

#endif // !_SPRITECOMPONENT_H_