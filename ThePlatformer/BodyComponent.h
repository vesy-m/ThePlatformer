#pragma once
#include "BaseGameObject.h"

#include <glm/glm.hpp>
#include "vectorMessage.h"

namespace GameComponents {
	class BodyComponent : BaseComponent
	{
	public:
		BodyComponent(GameObjects::BaseGameObject *);
		~BodyComponent();

		COMPONENT_TYPE getType();
		void Update();
		void Init();
		void sendMessage(Message*);

		void Integrate(float dt);
		void AddForce(float x, float y);
		void AddVelocity(float x, float y);

		void setPositionX(int x);
		void setPositionY(int y);
		int getPositionX();
		int getPositionY();

	private:
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 acceleration;
		float mass;
		glm::vec2 gravity;
		glm::vec2 forces;
		bool onGround;
	};
}

