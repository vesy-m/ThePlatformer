#include "Collider.h"

namespace GameComponents {
	BoxCollider::BoxCollider()
	{}

	BoxCollider::BoxCollider(glm::vec2 min, glm::vec2 max)
	{
		this->min = min;
		this->max = max;
	}

	BoxCollider::~BoxCollider()
	{}

	COMPONENT_TYPE BoxCollider::getType()
	{
		return COMPONENT_TYPE::PHYSIC;
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
		return COMPONENT_TYPE::PHYSIC;
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
		return COMPONENT_TYPE::PHYSIC;
	}

	void HexagonCollider::Update()
	{
		bool isCollide = false;
		glm::vec2 velocity = glm::vec2(0, 0);
		glm::vec2 pos = glm::vec2(this->composition->getX(), this->composition->getY());
		//pour tout les objects avec un collider
		//optimiser selon l'eloignement
		BoxCollider *other = new BoxCollider(glm::vec2(100, 480), glm::vec2(150, 510));
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
			pos = glm::vec2(pos.x, other->min.y - 1);
		}
		if (this->CollideTopLeft(other) || this->CollideDownLeft(other))
		{
			isCollide = true;
			velocity += glm::vec2(1, 0);
			pos = glm::vec2(other->max.x + 1, pos.y);
		}
		if (this->CollideTopRight(other) || this->CollideDownRight(other))
		{
			isCollide = true;
			velocity += glm::vec2(1, 0);
			pos = glm::vec2(other->min.x - 1, pos.y);
		}

		if (isCollide)
		{
			std::cout << "JE SUIS EN TRAIN DE COLLIDER PARCE QUE C'EST COOOOL !!!" << std::endl;
			CollisionMessage *msg = new CollisionMessage(pos, velocity);
			this->composition->SendMessage((Message*)msg);
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
		return (this->composition->getY() >= other->max.y);
	}

	bool HexagonCollider::CollideDown(BoxCollider *other)
	{
		return (this->composition->getY() + this->composition->getHeight() <= other->min.y);
	}

	bool HexagonCollider::CollideTopLeft(BoxCollider *other)
	{
		return ((this->composition->getX() <= other->min.x) || (this->composition->getY() + (this->composition->getHeight() / 5) >= other->max.y));
	}

	bool HexagonCollider::CollideTopRight(BoxCollider *other)
	{
		return ((this->composition->getX() + this->composition->getWidth() <= other->max.x) || (this->composition->getY() + (this->composition->getHeight() / 5) >= other->max.y));
	}

	bool HexagonCollider::CollideDownLeft(BoxCollider *other)
	{
		return ((this->composition->getX() <= other->min.x) || (this->composition->getY() + this->composition->getHeight() - this->composition->getHeight() / 5 <= other->min.y));
	}

	bool HexagonCollider::CollideDownRight(BoxCollider *other)
	{
		return ((this->composition->getX() + this->composition->getWidth() <= other->max.x) || (this->composition->getY() + this->composition->getHeight() - this->composition->getHeight() / 5 <= other->min.y));
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