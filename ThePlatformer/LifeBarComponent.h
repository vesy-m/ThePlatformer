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
	class LifeBarComponent : public BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	public:
		LifeBarComponent(GameObjects::BaseGameObject*, int color);
		virtual ~LifeBarComponent();
		virtual void sendMessage(GameMessage::Message*);
		virtual COMPONENT_TYPE getType() const;
		virtual void Update(double);
		virtual void Init();
	private:
		void drawSquare(int x, int y, int width, int height, int percent);
		const COMPONENT_TYPE type = COMPONENT_TYPE::LIFE_BAR;
		int life;
		float lifeMax;
		int widthLifeBar;
		int heightLifeBar;
		glm::vec3 barColor;
	};
}