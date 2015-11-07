#include "Projectile.h"


namespace GameObjects {
	Projectile::Projectile(GameObjects::BaseGameObject shooter) : BaseGameObject()
	{
		this->shooter = shooter;
	}


	Projectile::~Projectile()
	{
	}

	GameObjects::BaseGameObject Projectile::getShooter()
	{
		return this->shooter;
	}
}