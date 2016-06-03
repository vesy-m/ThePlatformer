#include "BoxCollider.h"
#include "AudioSystem.h"

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
		BoxCollider *A = (BoxCollider*)manifold->A;
		BoxCollider *B = (BoxCollider*)manifold->B;

		glm::vec2 positionA = glm::vec2(manifold->A->getComposition()->getX(), manifold->A->getComposition()->getY());
		glm::vec2 positionB = glm::vec2(manifold->B->getComposition()->getX(), manifold->B->getComposition()->getY());

		float x = (B->minPoint.x + (B->composition->getWidth() / 2)) - (A->minPoint.x + (A->composition->getWidth() / 2));
		float y = (B->minPoint.y + B->composition->getHeight() / 2) - (A->minPoint.y + A->composition->getHeight() / 2);
		glm::vec2 n = glm::vec2(x, y);

		float a_extent = (A->maxPoint.x - A->minPoint.x) / 2;
		float b_extent = (B->maxPoint.x - B->minPoint.x) / 2;

		float x_overlap = a_extent + b_extent - abs(n.x);

		if (x_overlap > 0)
		{
			float a_extent = (A->maxPoint.y - A->minPoint.y) / 2;
			float b_extent = (B->maxPoint.y - B->minPoint.y) / 2;

			float y_overlap = a_extent + b_extent - abs(n.y);

			if (y_overlap >= 0)
			{
				//if (this->getComposition()->getName().find("metalslug") != std::string::npos)
				//{
				//	std::cout << x_overlap << " "<< y_overlap << std::endl;
				//}
				if (x_overlap < y_overlap)
				{
					if (n.x < 0)
					{
						manifold->normal = glm::vec2(1, 0);
						manifold->penetration = ((positionB.x + manifold->B->getComposition()->getWidth()) - positionA.x) + 1;
						//if (this->getComposition()->getName().find("metalslug") != std::string::npos)
						//{
						//	std::cout << "RIGHT COLLISION" << std::endl;
						//}
					}
					else
					{
						manifold->normal = glm::vec2(-1, 0);
						manifold->penetration = ((positionA.x + manifold->A->getComposition()->getWidth()) - positionB.x) + 1;
						//if (this->getComposition()->getName().find("metalslug") != std::string::npos)
						//{
						//	std::cout << "LEFT COLLISION" << std::endl;
						//}
					}
					return true;
				}
				else
				{
					if (n.y < 0)
					{
						manifold->normal = glm::vec2(0, 1);
						manifold->penetration = ((positionB.y + manifold->B->getComposition()->getHeight()) - positionA.y) + 1;
						//if (this->getComposition()->getName().find("metalslug") != std::string::npos)
						//{
						//	std::cout << "DOWN COLLISION" << std::endl;
						//}
					}
					else
					{
						manifold->normal = glm::vec2(0, -1);
						manifold->penetration = (positionA.y + manifold->A->getComposition()->getHeight()) - positionB.y;
						//if (this->getComposition()->getName().find("metalslug") != std::string::npos)
						//{
						//	std::cout << "UP COLLISION" << std::endl;
						//}
					}
					return true;
				}
			}
		}
		return false;
	}

	COMPONENT_TYPE BoxCollider::getType() const
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
				if (this->composition->getType() == GameObjects::PLAYER || this->composition->getType() == GameObjects::PLAYER_BLOCK) {
					if (object->getType() == GameObjects::PROJECTILE || object->getType() == GameObjects::PROJECTILE_BREAK/* && object->getName().compare(this->composition->getName()) == 0*/)
						continue;
					else if (object->getType() == GameObjects::PLAYER || object->getType() == GameObjects::PLAYER_BLOCK)
						continue;
				}

				if (this->composition->getType() == GameObjects::PROJECTILE ||
					this->composition->getType() == GameObjects::PROJECTILE_BREAK) {
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
						if (!otherObject) GameTools::debugManager::getInstance().dAssert("BoxCollider otherObject is NULL");
						manifold->A = this;
						manifold->B = otherObject;
						GameObjects::objectType typeA = this->composition->getType();
						GameObjects::objectType typeB = otherObject->composition->getType();

						if (this->CollideWithBox(manifold))
						{
							if (typeA == GameObjects::PROJECTILE)
								std::cout << "PROJECTILE COLLISION" << std::endl;
							if (typeB == GameObjects::PROJECTILE)
								otherObject->composition->destroy(true);
							else if (typeA == GameObjects::PROJECTILE)
								this->composition->destroy(true);
							else if (typeA == GameObjects::PROJECTILE_BREAK && typeB != GameObjects::PLAYER)
							{
								this->composition->destroy(true);
								if (typeB != GameObjects::PLAYER_ATTACK)
									otherObject->composition->destroy(true);
							}
							if ((typeA == GameObjects::PROJECTILE && typeB == GameObjects::PLAYER) ||
								(typeA == GameObjects::PROJECTILE_BREAK && typeB == GameObjects::PLAYER) ||
								(typeA == GameObjects::PROJECTILE && typeB == GameObjects::PLAYER_ATTACK) ||
								(typeA == GameObjects::PROJECTILE_BREAK && typeB == GameObjects::PLAYER_ATTACK))
							{
								otherObject->composition->sendMessage(new GameMessage::DamageMessage(GameMessage::DamageMessage::PROJECTILE, this->composition->getPower()));
								if (typeA == GameObjects::PROJECTILE_BREAK)
									this->composition->destroy(true);
							}
							else if ((typeA == GameObjects::PLAYER && typeB == GameObjects::PROJECTILE) ||
									 (typeA == GameObjects::PLAYER && typeB == GameObjects::PROJECTILE_BREAK) ||
									 (typeA == GameObjects::PLAYER_ATTACK && typeB == GameObjects::PROJECTILE) ||
									 (typeA == GameObjects::PLAYER_ATTACK && typeB == GameObjects::PROJECTILE_BREAK))
							{
								this->sendMessage(new GameMessage::DamageMessage(GameMessage::DamageMessage::PROJECTILE, otherObject->composition->getPower()));
								if (typeB == GameObjects::PROJECTILE || typeB == GameObjects::PROJECTILE_BREAK)
									otherObject->composition->destroy(true);
								continue;
							}
							else if (typeA == GameObjects::PLAYER_ATTACK && typeB == GameObjects::PLAYER)
							{
								otherObject->composition->sendMessage(new GameMessage::DamageMessage(GameMessage::DamageMessage::DASH, this->composition->getPower()));
								continue;
							}
							else if ((typeA == GameObjects::PLAYER_BLOCK && typeB == GameObjects::PLAYER_ATTACK) ||
									 (typeA == GameObjects::PLAYER_ATTACK && typeB == GameObjects::PROJECTILE) ||
									 (typeA == GameObjects::PLAYER_ATTACK && typeB == GameObjects::PROJECTILE_BREAK) ||
									 (typeA == GameObjects::PROJECTILE && typeB == GameObjects::PLAYER_ATTACK) ||
									 (typeA == GameObjects::PROJECTILE_BREAK && typeB == GameObjects::PLAYER_ATTACK)) {
								continue;
							}

							ResolveCollision(manifold);
							collide = true;
						}
					}
					delete manifold;
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