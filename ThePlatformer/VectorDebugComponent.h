#pragma once

#include "BaseGameObject.h"
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include "vectorMessage.h"
#include "debugManager.h"
#include "glm\glm.hpp"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class VectorDebugComponent : public BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	public:
		VectorDebugComponent(GameObjects::BaseGameObject*, std::string);
		virtual ~VectorDebugComponent();
		virtual void sendMessage(GameMessage::Message*);
		virtual COMPONENT_TYPE getType() const;
		virtual void Update(double);
		virtual void Init();
	private:
		void drawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
		void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius);
		const COMPONENT_TYPE type = COMPONENT_TYPE::DEBUGVECTOR;
		glm::vec2 velocity;
		std::string typeDraw;
	};
}