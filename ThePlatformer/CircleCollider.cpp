#include "CircleCollider.h"
#include "BoxCollider.h"

namespace GameComponents {
	CircleCollider::CircleCollider(GameObjects::BaseGameObject *object) : Collider(object)
	{
		this->radius = this->composition->getHeight() / 2;
		this->pos = glm::vec2(this->composition->getX() + this->composition->getWidth() / 2.0f, this->composition->getY() + this->composition->getHeight() / 2.0f);
	}

	CircleCollider::~CircleCollider()
	{
	}

	bool CircleCollider::CollideWithCircle(Manifold *manifold)
	{
		// Setup a couple pointers to each object
		CircleCollider *A = (CircleCollider*)manifold->A;
		CircleCollider *B = (CircleCollider*)manifold->B;

		// Vector from A to B
		glm::vec2 n = B->pos - A->pos;

		float r = A->radius + B->radius;

		if (glm::length(n) > r)
			return false;

		// Now, we resolve the manifold like a box
		glm::vec2 positionA = glm::vec2(manifold->A->composition->getX(), manifold->A->composition->getY());
		glm::vec2 positionB = glm::vec2(manifold->B->composition->getX(), manifold->B->composition->getY());
		glm::vec2 minA = glm::vec2(A->composition->getX(), A->composition->getY());
		glm::vec2 maxA = glm::vec2(A->composition->getX() + A->composition->getWidth(), A->composition->getY() + A->composition->getWidth());
		glm::vec2 minB = glm::vec2(B->composition->getX(), B->composition->getY());
		glm::vec2 maxB = glm::vec2(B->composition->getX() + B->composition->getWidth(), B->composition->getY() + B->composition->getWidth());

		// Vector from A to B
		float x = (minB.x + (B->composition->getWidth() / 2)) - (minA.x + (A->composition->getWidth() / 2));
		float y = (minB.y + (B->composition->getHeight() / 2)) - (minA.y + (A->composition->getHeight() / 2));
		glm::vec2 norm = glm::vec2(x, y);

		// Calculate half extents along x axis for each object
		float a_extent = (maxA.x - minA.x) / 2;
		float b_extent = (maxB.x - minB.x) / 2;

		// Calculate overlap on x axis
		float x_overlap = a_extent + b_extent - abs(norm.x);

		// SAT test on x axis
		if (x_overlap > 0)
		{
			// Calculate half extents along x axis for each object
			float a_extent = (maxA.y - minA.y) / 2;
			float b_extent = (maxB.y - minB.y) / 2;

			// Calculate overlap on y axis
			float y_overlap = a_extent + b_extent - abs(norm.y);

			// SAT test on y axis
			if (y_overlap >= 0)
			{
				// Find out which axis is axis of least penetration
				if (x_overlap < y_overlap)
				{
					// Point towards B knowing that n points from A to B
					if (norm.x < 0)
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
					if (norm.y < 0)
					{
						manifold->normal = glm::vec2(0, 1);
						manifold->penetration = ((positionB.y + manifold->B->composition->getHeight()) - positionA.y) + 0.1f;
					}
					else
					{
						manifold->normal = glm::vec2(0, -1);
						manifold->penetration = (positionA.y + manifold->A->composition->getHeight()) - positionB.y - 10;
					}
					return true;
				}
			}
		}
		return false;
	}

	bool CircleCollider::CollideWithBox(Manifold *manifold)
	{
		// Setup a couple pointers to each object
		CircleCollider *A = (CircleCollider*)manifold->A;
		BoxCollider *B = (BoxCollider*)manifold->B;

		glm::vec2 centerB = glm::vec2(manifold->B->composition->getX() + manifold->B->composition->getWidth() / 2.0f, manifold->B->composition->getY() + manifold->B->composition->getHeight() / 2.0f);

		// Vector from A to B
		glm::vec2 n = A->pos - centerB;

		// Closest point on A to center of B
		glm::vec2 closest = n;

		// Calculate half extents along each axis
		float x_extent = (B->max.x - B->min.x) / 2;
		float y_extent = (B->max.y - B->min.y) / 2;

		// Clamp point to edges of the AABB
		closest.x = Clamp(-x_extent, x_extent, closest.x);
		closest.y = Clamp(-y_extent, y_extent, closest.y);

		bool inside = false;

		// Circle is inside the AABB, so we need to clamp the circle's center
		// to the closest edge
		if (n == closest)
		{
			inside = true;

			// Find closest axis
			if (abs(n.x) > abs(n.y))
			{
				// Clamp to closest extent
				if (closest.x > 0)
					closest.x = x_extent;
				else
					closest.x = -x_extent;
			}

			// y axis is shorter
			else
			{
				// Clamp to closest extent
				if (closest.y > 0)
					closest.y = y_extent;
				else
					closest.y = -y_extent;
			}
		}

		glm::vec2 normal = n - closest;
		float d = std::pow(normal.length(), 2);
		float r = A->radius;

		// Early out of the radius is shorter than distance to closest point and
		// Circle not inside the AABB
		if (d > r * r && !inside)
			return false;


		// Now, we resolve the manifold like a box
		glm::vec2 positionA = glm::vec2(manifold->A->composition->getX(), manifold->A->composition->getY());
		glm::vec2 positionB = glm::vec2(manifold->B->composition->getX(), manifold->B->composition->getY());
		glm::vec2 minA = glm::vec2(A->composition->getX(), A->composition->getY());
		glm::vec2 maxA = glm::vec2(A->composition->getX() + A->composition->getWidth(), A->composition->getY() + A->composition->getWidth());

		// Vector from A to B
		float x = (B->min.x + (B->composition->getWidth() / 2)) - (minA.x + (A->composition->getWidth() / 2));
		float y = (B->min.y + B->composition->getHeight() / 2) - (minA.y + A->composition->getHeight() / 2);
		glm::vec2 norm = glm::vec2(x, y);

		// Calculate half extents along x axis for each object
		float a_extent = (maxA.x - minA.x) / 2;
		float b_extent = (B->max.x - B->min.x) / 2;

		// Calculate overlap on x axis
		float x_overlap = a_extent + b_extent - abs(norm.x);

		// SAT test on x axis
		if (x_overlap > 0)
		{
			// Calculate half extents along x axis for each object
			float a_extent = (maxA.y - minA.y) / 2;
			float b_extent = (B->max.y - B->min.y) / 2;

			// Calculate overlap on y axis
			float y_overlap = a_extent + b_extent - abs(norm.y);

			// SAT test on y axis
			if (y_overlap >= 0)
			{
				// Find out which axis is axis of least penetration
				if (x_overlap < y_overlap)
				{
					// Point towards B knowing that n points from A to B
					if (norm.x < 0)
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
					if (norm.y < 0)
					{
						manifold->normal = glm::vec2(0, 1);
						manifold->penetration = ((positionB.y + manifold->B->composition->getHeight()) - positionA.y) + 0.1f;
					}
					else
					{
						manifold->normal = glm::vec2(0, -1);
						manifold->penetration = (positionA.y + manifold->A->composition->getHeight()) - positionB.y - 10;
					}
					return true;
				}
			}
		}
		return false;
	}

	void CircleCollider::Update(double)
	{
		bool collide = false;

		this->pos = glm::vec2(this->composition->getX() + this->composition->getWidth() / 2.0f, this->composition->getY() + this->composition->getHeight() / 2.0f);;

		if (this->composition->getType() != GameObjects::NONE)
		{
			for each(GameObjects::BaseGameObject* object in GameSystems::ObjectFactory::getInstance().getCurrentLevel().getObjects())
			{
				if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER))
				{
					if (object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER) == this)
						continue;
					Collider* collider = (Collider*)object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER);
					Manifold *manifold = new Manifold();
					manifold->A = this;
					if (collider->getColliderType() == COLLIDER_TYPE::BOX)
					{
						BoxCollider *other = (BoxCollider*)object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER);
						manifold->B = other;
						if (this->CollideWithBox(manifold))
						{
							// Destroy projectiles on collision
							if (other->composition->getType() == GameObjects::PROJECTILE) other->composition->destroy(true);
							else if (this->composition->getType() == GameObjects::PROJECTILE) this->composition->destroy(true);


							ResolveCollision(manifold);
							collide = true;
						}
					}
					else if (collider->getColliderType() == COLLIDER_TYPE::CIRCLE)
					{
						CircleCollider *other = (CircleCollider*)object->getComponent(GameComponents::COMPONENT_TYPE::COLLIDER);
						manifold->B = other;
						if (this->CollideWithCircle(manifold))
						{
							// Destroy projectiles on collision
							if (other->composition->getType() == GameObjects::PROJECTILE) other->composition->destroy(true);
							else if (this->composition->getType() == GameObjects::PROJECTILE) this->composition->destroy(true);

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

	COLLIDER_TYPE CircleCollider::getColliderType()
	{
		return COLLIDER_TYPE::CIRCLE;
	}

	void CircleCollider::sendMessage(GameMessage::Message *message)
	{
		if (message->id == GameMessage::VELOCITY_VECTOR)
			this->velocity = ((GameMessage::VectorMessage*)message)->vector;
	}
}