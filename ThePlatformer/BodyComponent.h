#pragma once
#include "BaseGameObject.h"

#include <glm/glm.hpp>

namespace GameComponents {
	class BodyComponent : BaseComponent
	{
	public:
		BodyComponent(GameObjects::BaseGameObject *);
		~BodyComponent();

		COMPONENT_TYPE getType();
		void Update();
		void Init();
		void Integrate(float dt);
		void setPositionX(int x);
		void setPositionY(int y);
		int getPositionX();
		int getPositionY();

	private:
		glm::vec2 position;
		glm::vec2 velocity;
		double acceleration;
		double mass;
		double gravity;
		double forces;
	};
}

