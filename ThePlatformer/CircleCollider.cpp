#include "BoxCollider.h"
#include "CircleCollider.h"


namespace GameComponents {
	CircleCollider::CircleCollider(GameObjects::BaseGameObject *object) : ColliderComponent(object)
	{
	}


	CircleCollider::~CircleCollider()
	{
	}

	void CircleCollider::Init(void)
	{
		this->radius = this->composition->getHeight() / 2.0f;
		this->centerPos = glm::vec2(this->composition->getX() + this->composition->getHeight() / 2.0f, this->composition->getY() + this->composition->getHeight() / 2.0f);
		this->minPoint = glm::vec2(this->composition->getX(), this->composition->getY());
		this->maxPoint = glm::vec2(this->composition->getX() + this->composition->getHeight(), this->composition->getY() + this->composition->getHeight());
	}

	COMPONENT_TYPE CircleCollider::getType() const
	{
		return COMPONENT_TYPE::CIRCLE_COLLIDER;
	}

	void CircleCollider::Update(double dt)
	{
		this->centerPos = glm::vec2(this->composition->getX() + this->composition->getHeight() / 2.0f, this->composition->getY() + this->composition->getHeight() / 2.0f);
		this->minPoint = glm::vec2(this->composition->getX(), this->composition->getY());
		this->maxPoint = glm::vec2(this->composition->getX() + this->composition->getHeight(), this->composition->getY() + this->composition->getHeight());
		bool collide = false;

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
					if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER) == this) continue;

					Manifold *manifold = new Manifold();
					if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER)->getType() == COMPONENT_TYPE::BOX_COLLIDER)
					{
						BoxCollider *otherObject = dynamic_cast<BoxCollider*>(object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER));

						manifold->A = this;
						manifold->B = otherObject;
						if (CollideWithBox(manifold))
						{
							ResolveCollision(manifold);
							collide = true;
						}
					}
				}
			}
			if (!collide)
				this->composition->sendMessage(new GameMessage::Message(GameMessage::NO_COLLISION));
		}
	}

	bool CircleCollider::CollideWithBox(Manifold *manifold) 
	{
		CircleCollider *A = dynamic_cast<CircleCollider*>(manifold->A);
		BoxCollider *B = dynamic_cast<BoxCollider*>(manifold->B);
		
		bool inside = false;

		glm::vec2 closestPoint = glm::vec2(Clamp(A->centerPos.x, B->minPoint.x, B->maxPoint.x),
										   Clamp(A->centerPos.y, B->minPoint.y, B->maxPoint.y));

		float x_extent = (A->maxPoint.x - A->minPoint.x) / 2;
		float y_extent = (A->maxPoint.y - A->minPoint.y) / 2;

		glm::vec2 velocity = A->velocity;

		glm::vec2 fakeCenterPos = A->centerPos;

		if (A->centerPos == closestPoint)
		{
			std::cout << "Clamp" << std::endl;

			inside = true;

			fakeCenterPos += glm::normalize(-A->velocity) * A->radius;
		}

		glm::vec2 fakeDistance = fakeCenterPos - closestPoint;


		glm::vec2 compass[] = {
			glm::vec2(0.0f, 1.0f),	// down
			glm::vec2(1.0f, 0.0f),	// right
			glm::vec2(0.0f, -1.0f),	// up
			glm::vec2(-1.0f, 0.0f)	// left
		};
		float max = 0.0f;
		int dir = -1;
		for (int i = 0; i < 4; i++)
		{
			float dot_product = glm::dot(glm::normalize(fakeDistance), compass[i]);
			if (dot_product > max)
			{
				max = dot_product;
				dir = i;
			}
		}

		glm::vec2 distance = A->centerPos - closestPoint;

		if (glm::length(distance) <= A->radius)
		{
			if (dir == 0 || dir == 2) {
				manifold->normal = compass[dir];
				if (dir == 0)
					manifold->penetration = (A->radius - std::abs(distance.y)) + 0.1f;
				else
					manifold->penetration = (A->radius - std::abs(distance.y));
			}
			else {
				manifold->normal = compass[dir];
				manifold->penetration = (A->radius - std::abs(distance.x));
			}
			return true;
		}
		return false;
	}

	void CircleCollider::sendMessage(GameMessage::Message *message)
	{
		if (message->id == GameMessage::VELOCITY_VECTOR)
			this->velocity = ((GameMessage::VectorMessage*)message)->vector;
	}
}
