#include "Collider.h"

namespace GameComponents {

	BoxCollider::BoxCollider(GameObjects::BaseGameObject *object) : Collider(object)
	{
		this->min = glm::vec2(this->composition->getX(), this->composition->getY());
		this->max = glm::vec2(this->composition->getX() + this->composition->getWidth(), this->composition->getY() + this->composition->getHeight());
	}

	BoxCollider::~BoxCollider()
	{
	}

	bool BoxCollider::CollideWithBox(Manifold *manifold)
	{
		// Setup a couple pointers to each object
		BoxCollider *A = (BoxCollider*)manifold->A;
		BoxCollider *B = (BoxCollider*)manifold->B;

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
					}
					else
					{
						manifold->normal = glm::vec2(-1, 0);
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
					}
					else
					{
						manifold->normal = glm::vec2(0, -1);
					}
					manifold->penetration = y_overlap;
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

	float DotProduct(glm::vec2 a, glm::vec2 b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	void ResolveCollision(Manifold *manifold) // A changer à terme
	{
		float massA = 20.0f;
		float massB = 100.0f;

		glm::vec2 positionA = glm::vec2(manifold->A->composition->getX(), manifold->A->composition->getY());
		glm::vec2 positionB = glm::vec2(manifold->B->composition->getX(), manifold->B->composition->getY());

		float TotalInvertMass = massA + massB;

		float penetration = 0.0f;

		if (manifold->normal.y == -1)
			penetration = (positionA.y + manifold->A->composition->getHeight()) - positionB.y;
		else if (manifold->normal.y == 1)
			penetration = (positionB.y + manifold->B->composition->getHeight()) - positionA.y;
		else if (manifold->normal.x == -1)
			penetration = ((positionA.x + manifold->A->composition->getWidth()) - positionB.x) + 1;
		else if (manifold->normal.x == 1)
			penetration = ((positionB.x + manifold->B->composition->getWidth()) - positionA.x) + 1;


		/*glm::vec2 movePerIMass = manifold->normal * (penetration / TotalInvertMass);
		glm::vec2 addPos = movePerIMass * (1 / massA);
		addPos += -movePerIMass * (1 / massB);*/

		glm::vec2 addPos = manifold->normal * penetration;

		glm::vec2 newVec = ((BoxCollider*)manifold->A)->velocity;
		if (manifold->normal.y != 0)
			newVec.y = 0;
		else if (manifold->normal.x != 0)
			newVec.x = 0;

		CollisionMessage *msg = new CollisionMessage(newVec, addPos);

		//std::cout << "Velocity is (" << msg->velocity.x << "," << msg->velocity.y << ")" << std::endl;
		manifold->A->composition->sendMessage((Message*)msg);

		// Calculate relative velocity
		//glm::vec2 rv = -((BoxCollider*)manifold->A)->velocity;

		// Calculate relative velocity in terms of the normal direction
		//float velAlongNormal = DotProduct(rv, manifold->normal);

		// Do not resolve if velocities are separating
		//if (velAlongNormal > 0)
		//	return;

		// Calculate restitution
		//float e = min(A.restitution, B.restitution)
		//float e = 0;
		//float massA = 20.0f;
		//float massB = 1000.0f;

		// Calculate impulse scalar
		//float j = -(1 + e) * velAlongNormal;
		//j /= 1 / A.mass + 1 / B.mass;
		//j /= 1 / massA + 1 / massB;

		// Apply impulse
		//glm::vec2 impulse = j * manifold->normal;
		//float massSum = massA + massB;
		//float ratio = massA / massSum;
		//glm::vec2 minuValue = impulse / massA;
		//glm::vec2 test = ((BoxCollider*)manifold->A)->velocity - minuValue;
		//CollisionMessage *msg = new CollisionMessage(test);
		//CollisionMessage *msg = new CollisionMessage(((BoxCollider*)manifold->A)->velocity - ratio * impulse);
		//msg->velocity.y -= 9.8f; // Valeur de la gravité

		// Positional Correction
		/*const float percent = 0.4f;
		const float slop = 0.01f;
		float massInvA = 1 / massA;
		float massInvB = 0;
		glm::vec2 correction = (std::max(manifold->penetration - slop, 0.0f) / (massInvA + massInvB)) * percent * manifold->normal;
		msg->velocity -= massInvA * correction;*/


		//A.velocity -= 1 / A.mass * impulse;
		//B.velocity += 1 / B.mass * impulse;
	}

	void BoxCollider::Update(double)
	{
		bool collide = false;

		this->min = glm::vec2(this->composition->getX(), this->composition->getY());
		this->max = glm::vec2(this->composition->getX() + this->composition->getWidth(), this->composition->getY() + this->composition->getHeight());

		if (this->composition->getType() == GameObjects::PLAYER)
		{
			for each(GameObjects::BaseGameObject* object in GameSystems::ObjectFactory::getInstance().getCurrentLevel().getObjects())
			{
				if (!object->getComponents(GameComponents::COMPONENT_TYPE::COLLIDER).empty())
				{
					if (object->getComponents(GameComponents::COMPONENT_TYPE::COLLIDER)[0] == this)
						continue;
					BoxCollider *other = (BoxCollider*)object->getComponents(GameComponents::COMPONENT_TYPE::COLLIDER)[0];
					Manifold *manifold = new Manifold();
					manifold->A = this;
					manifold->B = other;
					if (this->CollideWithBox(manifold))
					{
						std::cout << "JE COLLIDE ! Normal is (" << manifold->normal.x << "," << manifold->normal.y << ")" << std::endl;
						ResolveCollision(manifold);
						collide = true;
					}
				}
			}
			if (!collide)
			{
				std::cout << "JE NE COLLIDE PAS" << std::endl;
				this->composition->sendMessage(new Message(Message::NO_COLLISION));
			}
		}
	}

	void BoxCollider::sendMessage(Message *message)
	{
		if (message->id == Message::VELOCITY_VECTOR)
			this->velocity = ((VectorMessage*)message)->vector;
	}

	CircleCollider::CircleCollider(float radius, glm::vec2 pos, GameObjects::BaseGameObject *object) : Collider(object)
	{
		this->radius = radius;
		this->pos = pos;
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
		r *= r;

		if (sqrt(glm::length(n)) > r)
			return false;

		// Circles have collided, now compute manifold
		float d = glm::length(n); // perform actual sqrt

								  // If distance between circles is not zero
		if (d != 0)
		{
			// Distance is difference between radius and distance
			manifold->penetration = r - d;

			// Utilize our d since we performed sqrt on it already within Length( )
			// Points from A to B, and is a unit vector
			//manifold->normal = t / d;
			return true;
		}

		// Circles are on same position
		else
		{
			// Choose random (but consistent) values
			manifold->penetration = A->radius;
			manifold->normal = glm::vec2(1, 0);
			return true;
		}
	}

	COLLIDER_TYPE CircleCollider::getColliderType()
	{
		return COLLIDER_TYPE::CIRCLE;
	}

	CollisionMessage::CollisionMessage(glm::vec2 velocity, glm::vec2 position) : Message(COLLISION)
	{
		this->velocity = velocity;
		this->position = position;
	}

	CollisionMessage::~CollisionMessage()
	{
	}
}





























/*BoxCollider::BoxCollider(GameObjects::BaseGameObject *object) : BaseComponent(object)
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

void HexagonCollider::sendMessage(Message*) {

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
for each(GameObjects::BaseGameObject* object in GameSystems::ObjectFactory::getInstance().getCurrentLevel().getObjects())
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
this->composition->sendMessage((Message*)msg);
}
}
}
if (isCollide == false)
{
this->composition->sendMessage(new Message(Message::NO_COLLISION));
}
}

void HexagonCollider::Init()
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

*/
