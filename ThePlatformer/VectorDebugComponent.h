#pragma once

#include "BaseGameObject.h"

#include <SFML/OpenGL.hpp>

namespace GameComponents {

	class VectorDebugComponent : BaseComponent
	{
	public:
		VectorDebugComponent();
		~VectorDebugComponent();
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::DEBUGVECTOR;
	};

}