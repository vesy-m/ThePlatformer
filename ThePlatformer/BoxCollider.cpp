#include "BoxCollider.h"

namespace GameComponents {
	BoxCollider::BoxCollider(GameObjects::BaseGameObject *object) : Collider(object)
	{
	}

	BoxCollider::~BoxCollider()
	{
	}

	void BoxCollider::Init(void) {
		this->min = glm::vec2(this->composition->getX(), this->composition->getY());
		this->max = glm::vec2(this->composition->getX() + this->composition->getWidth(), this->composition->getY() + this->composition->getHeight());
	}

	bool BoxCollider::CollideWithBox(Manifold *manifold)
	{
		// Setup a couple pointers to each object
		BoxCollider *A = (BoxCollider*)manifold->A;
		BoxCollider *B = (BoxCollider*)manifold->B;

		glm::vec2 positionA = glm::vec2(manifold->A->composition->getX(), manifold->A->composition->getY());
		glm::vec2 positionB = glm::vec2(manifold->B->composition->getX(), manifold->B->composition->getY());

		// Vector from A to B
		float x = (B->min.x + (B->composition->getWidth() / 2)) - (A->min.x + (A->composition->getWidth() / 2));
		float y = (B->min.y + B->composition->getHeight() / 2) - (A->min.y + A->composition->getHeight() / 2);
		glm::vec2 n = glm::vec2(x, y);

		// Calculate half extents along x axis for each object
		float a_extent = (A->max.x - A->min.x) / 2;
		float b_extent = (B->max.x - B->min.x) / 2;

		// Calculate overlap on x axis
		float x_overlap = a_extent + b_extent - abs(n.x);

		// SAT test on x axis
		if (x_overlap > 0)
		{
			// Calculate half extents along x axis for each object
			float a_extent = (A->max.y - A->min.y) / 2;
			float b_extent = (B->max.y - B->min.y) / 2;

			// Calculate overlap on y axis
			float y_overlap = a_extent + b_extent - abs(n.y);

			// SAT test on y axis
			if (y_overlap >= 0)
			{
				// Find out which axis is axis of least penetration
				if (x_overlap < y_overlap)
				{
					// Point towards B knowing that n points from A to B
					if (n.x < 0)
					{
						manifold->normal = glm::vec2(1, 0);
						manifold->penetration = ((positionB.x + manifold->B->composition->getWidth()) - positionA.x) + 1;
					}
					else
					{
						manifold->normal = glm::vec2(-1, 0);
						manifold->penetration = ((positionA.x + manifold->A->composition->getWidth()) - positionB.x) + 1;
					}
					manifold->penetration = x_overlap;
					return true;
				}
				else
				{
					// Point toward B knowing that n points from A to B
					if (n.y < 0)
					{
						manifold->normal = glm::vec2(0, 1);
						manifold->penetration = ((positionB.y + manifold->B->composition->getHeight()) - positionA.y) + 0.1f;
					}
					else
					{
						manifold->normal = glm::vec2(0, -1);
						manifold->penetration = (positionA.y + manifold->A->composition->getHeight()) - positionB.y;
					}
					return true;
				}
			}
		}
		return false;
	}

	COLLIDER_TYPE BoxCollider::getColliderType()
	{
		return COLLIDER_TYPE::BOX;
	}

	void BoxCollider::Update(double)
	{
		bool collide = false;

		this->min = glm::vec2(this->composition->getX(), this->composition->getY());
		this->max = glm::vec2(this->composition->getX() + this->composition->getWidth(), this->composition->getY() + this->composition->getHeight());

		if (this->composition->getType() != GameObjects::NONE)
		{
			for each(GameObjects::BaseGameObject* object in GameSystems::ObjectFactory::getInstance().getCurrentObjects())
			{
				if (this->composition->getType() == GameObjects::PLAYER) {
					if (object->getType() == GameObjects::PROJECTILE && object->getName().compare(this->composition->getName()) == 0)
						continue;
					else if (object->getType() == GameObjects::PLAYER)
						continue;
				}

				if (this->composition->getType() == GameObjects::PROJECTILE) {
					if (object->getType() == GameObjects::PLAYER && object->getName().compare(this->composition->getName()) == 0)
						continue;
					if (object->getType() == GameObjects::PROJECTILE)
						continue;
				}
				if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER))
				{
					if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER) == this) continue;
					BoxCollider *other = dynamic_cast<BoxCollider*>(object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER));
					assert(other != NULL);
					Manifold *manifold = new Manifold();
					manifold->A = this;
					manifold->B = other;
					if (this->CollideWithBox(manifold))
					{
						// Destroy projectiles on collision
						if (other->composition->getType() == GameObjects::PROJECTILE) other->composition->destroy(true);
						else if (this->composition->getType() == GameObjects::PROJECTILE) this->composition->destroy(true);

						if (this->composition->getType() == GameObjects::PROJECTILE && other->composition->getType() == GameObjects::PLAYER)
							other->composition->destroy(true);
						else if (this->composition->getType() == GameObjects::PLAYER && other->composition->getType() == GameObjects::PROJECTILE)
							this->composition->destroy(true);

						ResolveCollision(manifold);
						collide = true;
					}
				}
			}
			if (!collide)
			{
				this->composition->sendMessage(new GameMessage::Message(GameMessage::Message::NO_COLLISION));
			}
		}
	}

	void BoxCollider::sendMessage(GameMessage::Message *message)
	{
		if (message->id == GameMessage::Message::VELOCITY_VECTOR)
			this->velocity = ((GameMessage::VectorMessage*)message)->vector;
	}

	void ResolveCollision(Manifold *manifold)
	{
		glm::vec2 positionA = glm::vec2(manifold->A->composition->getX(), manifold->A->composition->getY());
		glm::vec2 positionB = glm::vec2(manifold->B->composition->getX(), manifold->B->composition->getY());

		float penetration = manifold->penetration;
		float bounce = 0.0;

		glm::vec2 addPos = manifold->normal * penetration;

		glm::vec2 newVelocity = ((BoxCollider*)manifold->A)->velocity;
		if (manifold->normal.y != 0) {
			if (newVelocity.y >= -1 && newVelocity.y <= 1) newVelocity.y = 0.0;
			else newVelocity.y *= -bounce;
		}
		if (manifold->normal.x != 0) {
			if (newVelocity.x >= -1 && newVelocity.x <= 1) newVelocity.x = 0.0;
			else newVelocity.x *= -bounce;
		}

		GameMessage::CollisionMessage *msg = new GameMessage::CollisionMessage(newVelocity, addPos);
		manifold->A->composition->sendMessage((GameMessage::Message*)msg);
	}
}