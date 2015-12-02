#pragma once
#include "BaseGameObject.h"
#include <SFML/OpenGL.hpp>
#include <il.h>
#include <cstdio>
#include <string>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SpriteSheet.h"
#include "AimMessage.h"
#include "ObjectFactory.h"

#define TEXTURE_LOAD_ERROR 0

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class AimComponent : public BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		AimComponent(GameObjects::BaseGameObject*, const std::string&);
	public:
		virtual ~AimComponent();
		virtual COMPONENT_TYPE getType();
		virtual void Update(double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
	private:
		GameTools::SpriteSheet *sheet;
		std::string _fileName;

		glm::vec2 direction;
	};
}

