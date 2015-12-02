#include "BoxCollider.h"

namespace GameComponents {
	BoxCollider::BoxCollider(GameObjects::BaseGameObject *object) : ColliderComponent(object)
	{
	}

	BoxCollider::~BoxCollider()
	{
	}

	void BoxCollider::Init(void) {
		this->centerPos = glm::vec2(this->composition->getX() + this->composition->getWidth() / 2.0f, this->composition->getY() + this->composition->getHeight() / 2.0f);
		this->minPoint = glm::vec2(this->composition->getX(), this->composition->getY());
		this->maxPoint = glm::vec2(this->composition->getX() + this->composition->getWidth(), this->composition->getY() + this->composition->getHeight());
	}

	bool BoxCollider::CollideWithBox(Manifold *manifold)
	{
		// Setup a couple pointers to each object
		BoxCollider *A = (BoxCollider*)manifold->A;
		BoxCollider *B = (BoxCollider*)manifold->B;

		glm::vec2 positionA = glm::vec2(manifold->A->getComposition()->getX(), manifold->A->getComposition()->getY());
		glm::vec2 positionB = glm::vec2(manifold->B->getComposition()->getX(), manifold->B->getComposition()->getY());

		// Vector from A to B
		float x = (B->minPoint.x + (B->composition->getWidth() / 2)) - (A->minPoint.x + (A->composition->getWidth() / 2));
		float y = (B->minPoint.y + B->composition->getHeight() / 2) - (A->minPoint.y + A->composition->getHeight() / 2);
		glm::vec2 n = glm::vec2(x, y);

		// Calculate half extents along x axis for each object
		float a_extent = (A->maxPoint.x - A->minPoint.x) / 2;
		float b_extent = (B->maxPoint.x - B->minPoint.x) / 2;

		// Calculate overlap on x axis
		float x_overlap = a_extent + b_extent - abs(n.x);

		// SAT test on x axis
		if (x_overlap > 0)
		{
			// Calculate half extents along x axis for each object
			float a_extent = (A->maxPoint.y - A->minPoint.y) / 2;
			float b_extent = (B->maxPoint.y - B->minPoint.y) / 2;

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
						manifold->penetration = ((positionB.x + manifold->B->getComposition()->getWidth()) - positionA.x) + 1;
					}
					else
					{
						manifold->normal = glm::vec2(-1, 0);
						manifold->penetration = ((positionA.x + manifold->A->getComposition()->getWidth()) - positionB.x) + 1;
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
						manifold->penetration = ((positionB.y + manifold->B->getComposition()->getHeight()) - positionA.y) + 0.1f;
					}
					else
					{
						manifold->normal = glm::vec2(0, -1);
						manifold->penetration = (positionA.y + manifold->A->getComposition()->getHeight()) - positionB.y;
					}
					return true;
				}
			}
		}
		return false;
	}

	COMPONENT_TYPE BoxCollider::getType()
	{
		return COMPONENT_TYPE::BOX_COLLIDER;
	}

	void BoxCollider::Update(double)
	{
		this->centerPos = glm::vec2(this->composition->getX() + this->composition->getWidth() / 2.0f, this->composition->getY() + this->composition->getHeight() / 2.0f);
		this->minPoint = glm::vec2(this->composition->getX(), this->composition->getY());
		this->maxPoint = glm::vec2(this->composition->getX() + this->composition->getWidth(), this->composition->getY() + this->composition->getHeight());

		bool collide = false;

		this->minPoint = glm::vec2(this->composition->getX(), this->composition->getY());
		this->maxPoint = glm::vec2(this->composition->getX() + this->composition->getWidth(), this->composition->getY() + this->composition->getHeight());

		if (this->composition->getType() != GameObjects::NONE)
		{
			std::list<GameObjects::BaseGameObject*> listObjects = GameSystems::ObjectFactory::getInstance().getCurrentObjects();
			for each(GameObjects::BaseGameObject* object in listObjects)
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
				}
				if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER))
				{
					if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER) == this) {
						continue;
					}
					Manifold *manifold = new Manifold();
					if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER)->getType() == COMPONENT_TYPE::BOX_COLLIDER)
					{
						BoxCollider *otherObject = dynamic_cast<BoxCollider*>(object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER));
						assert(otherObject != NULL);
						manifold->A = this;
						manifold->B = otherObject;
						if (this->CollideWithBox(manifold))
						{
							if (this->composition->getType() == GameObjects::PROJECTILE)
								std::cout << "PROJECTILE COLLISION" << std::endl;
							// Destroy projectiles on collision
							if (otherObject->composition->getType() == GameObjects::PROJECTILE) otherObject->composition->destroy(true);
							else if (this->composition->getType() == GameObjects::PROJECTILE) this->composition->destroy(true);

							if (this->composition->getType() == GameObjects::PROJECTILE &&
								otherObject->composition->getType() == GameObjects::PLAYER)
							{
								otherObject->composition->sendMessage(new GameMessage::DamageMessage(this->composition->getPower()));
							}
							else if (this->composition->getType() == GameObjects::PLAYER &&
									 otherObject->composition->getType() == GameObjects::PROJECTILE)
							{
								otherObject->composition->sendMessage(new GameMessage::DamageMessage(otherObject->composition->getPower()));
							}

							ResolveCollision(manifold);
							collide = true;
						}
					}
				}
			}
			if (!collide)
			{
				this->composition->sendMessage(new GameMessage::Message(GameMessage::NO_COLLISION));
			}
		}
	}

	void BoxCollider::sendMessage(GameMessage::Message *message)
	{
		if (message->id == GameMessage::VELOCITY_VECTOR)
			this->velocity = ((GameMessage::VectorMessage*)message)->vector;
	}
}