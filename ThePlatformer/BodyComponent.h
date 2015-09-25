#pragma once
#include "BaseGameObject.h"

namespace GameComponents {
	class BodyComponent : BaseComponent
	{
	public:
		BodyComponent(GameObjects::BaseGameObject *composition);
		~BodyComponent();

		COMPONENT_TYPE getType();
		void Update();
		void Init();

	private:
		GameObjects::BaseGameObject *composition;
	};
}

