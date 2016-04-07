#pragma once

#include "BaseComponent.h"
#include "ObjectFactory.h"
#include "MouseMessageMove.h"
#include "MouseMessageClick.h"

namespace GameComponents {
	class EditorCaseSelectorComponent : public BaseComponent
	{
		friend class GameSystems::ObjectFactory;
		friend class GameTools::EditorManager;

	public:
		~EditorCaseSelectorComponent();
		void Update(double dt);
		void Init();
		void sendMessage(GameMessage::Message*);
		virtual COMPONENT_TYPE getType() const;
	private:
		EditorCaseSelectorComponent(GameObjects::BaseGameObject * object);
		const COMPONENT_TYPE type = COMPONENT_TYPE::CASE_SELECTOR;


	};
}
