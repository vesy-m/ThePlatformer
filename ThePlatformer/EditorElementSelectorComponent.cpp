#include "EditorElementSelectorComponent.h"
#include "EditorManager.h"

namespace GameComponents {

	EditorElementSelectorComponent::EditorElementSelectorComponent(GameObjects::BaseGameObject* object, int position) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->position = position;
	}


	EditorElementSelectorComponent::~EditorElementSelectorComponent()
	{
	}

	COMPONENT_TYPE EditorElementSelectorComponent::getType() const
	{
		return this->type;
	}

	void EditorElementSelectorComponent::Update(double dt)
	{

	}

	void EditorElementSelectorComponent::Init()
	{
	}

	void EditorElementSelectorComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::MOUSE_WHEEL:
			int delta = ((GameMessage::MouseMessageWheel*)message)->wheelDelta;
			if (delta < 0) {
				int minValue =	GameTools::EditorManager::getInstance().midValue +
								GameTools::EditorManager::getInstance().maxSpace * -1 + 
								GameTools::EditorManager::getInstance().HWCase * this->position;
				while (delta < 0 && this->composition->getY() != minValue) {
					this->composition->setY(this->composition->getY() - GameTools::EditorManager::getInstance().HWCase);
					delta++;
				}
			}
			else if (delta > 0) {
				int maxValue =	GameTools::EditorManager::getInstance().midValue +
								GameTools::EditorManager::getInstance().HWCase * this->position;
				while (delta > 0 && this->composition->getY() != maxValue) {
					this->composition->setY(this->composition->getY() + GameTools::EditorManager::getInstance().HWCase);
					delta--;
				}
			}
			if (this->composition->getY() == GameTools::EditorManager::getInstance().midValue) {
				GameTools::EditorManager::getInstance().setSelection(this->position);
			}
			break;
		};
	}

}