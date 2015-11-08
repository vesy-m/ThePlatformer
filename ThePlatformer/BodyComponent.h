#pragma once
#include <glm/glm.hpp>
#include "Collider.h"
#include "VectorMessage.h"
#include "BaseGameObject.h"
#include "ObjectFactory.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class BodyComponent : public BaseComponent
	{
		friend class ::GameSystems::ObjectFactory;
	public:
		virtual ~BodyComponent();

		virtual COMPONENT_TYPE getType();
		virtual void Update(double);
		virtual void Init();
		virtual void Init(float, bool);
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

