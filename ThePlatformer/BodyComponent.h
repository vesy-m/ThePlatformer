#pragma once
#include <glm/glm.hpp>
#include "Collider.h"
#include "VectorMessage.h"
#include "BaseGameObject.h"
#include "ObjectFactory.h"

namespace GameComponents {
	class BodyComponent : BaseComponent
	{
		friend class ::GameSystems::ObjectFactory;
	public:
		enum Direction {
			LEFT,
			TOP_LEFT,
			RIGHT,
			TOP_RIGHT
		};

		~BodyComponent();

		COMPONENT_TYPE getType();
		void Update(double);
		void Init();
		void Init(float, Direction);
		void sendMessage(GameMessage::Message*);

		void Integrate(float dt);
		void AddForce(float x, float y);
		void AddVelocity(float x, float y);

		void setPositionX(int x);
		void setPositionY(int y);
		int getPositionX();
		int getPositionY();

	private:
		BodyComponent(GameObjects::BaseGameObject*);
		glm::vec2 position;
		glm::vec2 velocity;

		glm::vec2 acceleration;
		glm::vec2 gravity;
		glm::vec2 forces;
		glm::vec2 lastCollisionVelocity;
		float mass;
		bool onGround;
		bool isColliding;
	};
}

