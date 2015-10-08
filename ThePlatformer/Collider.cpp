#include "Collider.h"

namespace GameComponents {

	BoxCollider::BoxCollider(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		this->min = glm::vec2(this->composition->getX(), this->composition->getY());
		this->max = glm::vec2(this->composition->getX() + this->composition->getWidth(), this->composition->getY() + this->composition->getHeight());
	}

	BoxCollider::~BoxCollider()
	{}

	COMPONENT_TYPE BoxCollider::getType()
	{
		return COMPONENT_TYPE::COLLIDER;
	}

	void BoxCollider::Update()
	{
	}

	void BoxCollider::Init()
	{
	}

	void BoxCollider::sendMessage(Message *message)
	{
	}

	bool BoxCollider::Collide(BoxCollider *other)
	{
		// Exit with no intersection if found separated along an axis
		if (this->max.x < other->min.x || this->min.x > other->max.x)
			return false;
		if (this->max.y < other->min.y || this->min.y > other->max.y)
			return false;

		// No separating axis found, therefor there is at least one overlapping axis
		return true;
	}

	bool BoxCollider::Collide(CircleCollider * other)
	{
		return false;
	}

	CircleCollider::CircleCollider()
	{}

	CircleCollider::CircleCollider(float radius, glm::vec2 pos)
	{
		this->radius = radius;
		this->pos = pos;
	}

	CircleCollider::~CircleCollider()
	{}

	COMPONENT_TYPE CircleCollider::getType()
	{
		return COMPONENT_TYPE::COLLIDER;
	}

	void CircleCollider::Update()
	{
	}

	void CircleCollider::Init()
	{
	}

	void CircleCollider::sendMessage(Message *message)
	{
	}

	bool CircleCollider::Collide(BoxCollider * other)
	{
		return false;
	}

	bool CircleCollider::Collide(CircleCollider *other)
	{
		float r = this->radius + other->radius;
		r *= r;
		return r < pow((this->pos.x + other->pos.x), 2) + pow((this->pos.y + other->pos.y), 2);
	}


	HexagonCollider::HexagonCollider(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
	}

	HexagonCollider::~HexagonCollider()
	{}

	COMPONENT_TYPE HexagonCollider::getType()
	{
		return COMPONENT_TYPE::COLLIDER;
	}

	void HexagonCollider::Update()
	{
		bool isCollide = false;
		glm::vec2 velocity = glm::vec2(0, 0);
		glm::vec2 pos = glm::vec2(this->composition->getX(), this->composition->getY());
		//pour tout les objects avec un collider
		//optimiser selon l'eloignement
		//BoxCollider *other = new BoxCollider(glm::vec2(200, 450), glm::vec2(250, 500));
		for each(GameObjects::BaseGameObject* object in GameSystems::ObjectFactory::getInstance().getObjects())
		{
			if (!object->getComponents(GameComponents::COMPONENT_TYPE::COLLIDER).empty())
			{
				if (object->getComponents(GameComponents::COMPONENT_TYPE::COLLIDER)[0] == this)
					continue;
				BoxCollider *other = (BoxCollider*)object->getComponents(GameComponents::COMPONENT_TYPE::COLLIDER)[0];
				if (this->CollideTop(other))
				{
					isCollide = true;
					velocity += glm::vec2(0, 1);
					pos = glm::vec2(pos.x, other->max.y + 1);
				}
				if (this->CollideDown(other))
				{
					isCollide = true;
					velocity += glm::vec2(0, 1);
					pos = glm::vec2(pos.x, other->min.y - 42);
				}
				if (this->CollideTopLeft(other) && this->CollideDownLeft(other))
				{
					isCollide = true;
					velocity += glm::vec2(1, 0);
					pos = glm::vec2(other->max.x - 5, pos.y);
				}
				if (this->CollideTopRight(other) && this->CollideDownRight(other))
				{
					isCollide = true;
					velocity += glm::vec2(1, 0);
					pos = glm::vec2(other->min.x + 5, pos.y);
				}

				if (isCollide)
				{
					CollisionMessage *msg = new CollisionMessage(pos, velocity);
					this->composition->SendMessage((Message*)msg);
				}
			}
		}
		if (isCollide == false)
		{
			this->composition->SendMessage(new Message(Message::NO_COLLISION));
		}
	}

	void HexagonCollider::Init()
	{
	}

	void HexagonCollider::sendMessage(Message *message)
	{
	}

	bool HexagonCollider::CollideTop(BoxCollider *other)
	{
		return ((this->composition->getY() <= other->max.y && this->composition->getY() >= other->min.y) && (this->composition->getX() >= other->min.x && this->composition->getX() <= other->max.x));
	}

	bool HexagonCollider::CollideDown(BoxCollider *other)
	{
		return ((this->composition->getY() + this->composition->getHeight() >= other->min.y && this->composition->getY() + this->composition->getHeight() <= other->max.y) && (this->composition->getX() >= other->min.x && this->composition->getX() <= other->max.x));
	}

	bool HexagonCollider::CollideTopLeft(BoxCollider *other)
	{
		return ((this->composition->getX() >= other->min.x && this->composition->getX() <= other->max.x) && (this->composition->getY() + (this->composition->getHeight() / 5) <= other->max.y && this->composition->getY() + (this->composition->getHeight() / 5) >= other->min.y));
	}

	bool HexagonCollider::CollideTopRight(BoxCollider *other)
	{
		return ((this->composition->getX() + this->composition->getWidth() <= other->max.x && this->composition->getX() + this->composition->getWidth() >= other->min.x) && (this->composition->getY() + (this->composition->getHeight() / 5) <= other->max.y && this->composition->getY() + (this->composition->getHeight() / 5) >= other->min.y));
	}

	bool HexagonCollider::CollideDownLeft(BoxCollider *other)
	{
		return ((this->composition->getX() >= other->min.x && this->composition->getX() <= other->max.x) && (this->composition->getY() + this->composition->getHeight() - this->composition->getHeight() / 5 <= other->max.y && this->composition->getY() + this->composition->getHeight() - this->composition->getHeight() / 5 >= other->min.y));
	}

	bool HexagonCollider::CollideDownRight(BoxCollider *other)
	{
		return ((this->composition->getX() + this->composition->getWidth() <= other->max.x && this->composition->getX() + this->composition->getWidth() >= other->min.x) && (this->composition->getY() + this->composition->getHeight() - this->composition->getHeight() / 5 >= other->min.y && this->composition->getY() + this->composition->getHeight() - this->composition->getHeight() / 5 <= other->max.y));
	}

	CollisionMessage::CollisionMessage(glm::vec2 pos, glm::vec2 velocity) : Message(COLLISION)
	{
		this->pos = pos;
		this->velocity = velocity;
	}

	CollisionMessage::~CollisionMessage()
	{
	}
}