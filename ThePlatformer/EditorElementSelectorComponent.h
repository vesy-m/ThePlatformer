#pragma once

#include "BaseComponent.h"
#include "ObjectFactory.h"
#include "MouseMessageWheel.h"

namespace GameComponents {
	class EditorElementSelectorComponent : public BaseComponent
	{
		friend class GameSystems::ObjectFactory;
		friend class GameTools::EditorManager;

	public:
		~EditorElementSelectorComponent();
		void Update(double dt);
		void Init();
		void sendMessage(GameMessage::Message*);
		virtual COMPONENT_TYPE getType();
	private:
		EditorElementSelectorComponent(GameObjects::BaseGameObject * object, int position);
		const COMPONENT_TYPE type = COMPONENT_TYPE::ELEMENT_SELECTOR;

		int position;

	};
}
