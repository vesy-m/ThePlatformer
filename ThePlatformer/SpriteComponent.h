#pragma once
#ifndef _SPRITECOMPONENT_H_
#define _SPRITECOMPONENT_H_

#include "BaseGameObject.h"

#include <SFML/OpenGL.hpp>
#include <il.h>
#include <cstdio>
#include <string>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SpriteSheet.h"
#include "ObjectFactory.h"

#define TEXTURE_LOAD_ERROR 0

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {

	class SpriteComponent : BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		SpriteComponent(GameObjects::BaseGameObject*, const std::string&);
	public:
		
		~SpriteComponent();
		COMPONENT_TYPE getType();
		void Update(double);
		void Init();
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
		int rotateNum;

	};
}

#endif // !_SPRITECOMPONENT_H_