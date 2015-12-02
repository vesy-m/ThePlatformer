#include "Collider.h"

namespace GameComponents {
	
	void ColliderComponent::ResolveCollision(Manifold * manifold)
	{
		glm::vec2 positionA = glm::vec2(manifold->A->composition->getX(), manifold->A->composition->getY());
		glm::vec2 positionB = glm::vec2(manifold->B->composition->getX(), manifold->B->composition->getY());

		float penetration = manifold->penetration;
		float bounce = manifold->A->composition->getBounce();

		glm::vec2 addPos = manifold->normal * penetration;

		glm::vec2 newVelocity = ((ColliderComponent*)manifold->A)->velocity;
		if (manifold->normal.y != 0) {
			if (newVelocity.y >= -1 && newVelocity.y <= 1) newVelocity.y = 0.0;
			else newVelocity.y *= -bounce;
		}
		if (manifold->normal.x != 0) {
			if (newVelocity.x >= -1 && newVelocity.x <= 1) newVelocity.x = 0.0;
			else newVelocity.x *= -bounce;
		}

		/*if (newVelocity.y >= -5.0f)
			newVelocity.y = 0.0f;*/

		GameMessage::CollisionMessage *msg = new GameMessage::CollisionMessage(newVelocity, addPos, manifold->normal);
		manifold->A->composition->sendMessage((GameMessage::Message*)msg);
	}

	glm::vec2 ColliderComponent::ClampTest(glm::vec2 point, glm::vec2 minPoint, glm::vec2 maxPoint)
	{
		if ((point.x > minPoint.x && point.y > minPoint.y) && (point.x < maxPoint.x && point.y < maxPoint.y))
		{
			glm::vec2 diffMinPoint = glm::vec2(std::abs(point.x) - std::abs(minPoint.x), std::abs(point.y) - std::abs(minPoint.y));
			glm::vec2 diffMaxPoint = glm::vec2(std::abs(maxPoint.x) - std::abs(point.x), std::abs(maxPoint.y) - std::abs(point.y));
			if (diffMinPoint.x < diffMaxPoint.x)
				point.x = minPoint.x;
			else
				point.x = maxPoint.x;

			if (diffMaxPoint.y < diffMinPoint.y)
				point.y = maxPoint.y;
			else
				point.y = minPoint.y;

			return point;
		}
		
		if (point.x < minPoint.x)
			point.x = minPoint.x;
		else if (point.x > maxPoint.x)
			point.x = maxPoint.x;

		if (point.y < minPoint.y)
			point.y = minPoint.y;
		else if (point.y > maxPoint.y)
			point.y = maxPoint.y;

		return point;
	}

	float ColliderComponent::Clamp(float value, float min, float max)
	{
		return value < min ? min : value > max ? max : value;
	}

	float ColliderComponent::DotProduct(glm::vec2 a, glm::vec2 b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

}