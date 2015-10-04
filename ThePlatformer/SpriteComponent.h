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

	class SpriteComponent : BaseComponent
	{
	public:
		SpriteComponent(GameObjects::BaseGameObject *, const std::string &fileName);
		~SpriteComponent();
		COMPONENT_TYPE getType();
		void Update();
		void Init();
		void viewportReload();
		void sendMessage(Message*);
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::SPRITE;
		SpriteSheet *sheet;
		bool revertX;
		bool revertY;
		int currentFrame;
		int counter;
		std::string currentAnim;
		std::string _fileName;

	};
}

#endif // !_SPRITECOMPONENT_H_