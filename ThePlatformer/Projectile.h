#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "BaseGameObject.h"

namespace GameObjects {

	class Projectile : GameObjects::BaseGameObject
	{
	public:
		Projectile(GameObjects::BaseGameObject);
		~Projectile();

		GameObjects::BaseGameObject getShooter();

	private:
		GameObjects::BaseGameObject shooter;
	};
}

#endif // !_PROJECTILE_H_

