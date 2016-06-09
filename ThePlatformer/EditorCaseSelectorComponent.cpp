#include "EditorCaseSelectorComponent.h"
#include "EditorManager.h"

namespace GameComponents {

	EditorCaseSelectorComponent::EditorCaseSelectorComponent(GameObjects::BaseGameObject* object, int newCaseSize) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->caseSize = newCaseSize;
	}


	EditorCaseSelectorComponent::~EditorCaseSelectorComponent()
	{
	}

	COMPONENT_TYPE EditorCaseSelectorComponent::getType() const
	{
		return this->type;
	}

	void EditorCaseSelectorComponent::Update(double dt)
	{

	}

	void EditorCaseSelectorComponent::Init()
	{
	}

	void EditorCaseSelectorComponent::sendMessage(GameMessage::Message *message)
	{
		int newPosX = 0;
		int newPosY = 0;
		switch (message->id)
		{
		case GameMessage::MOUSE_MOVE:
			newPosX = ((GameMessage::MouseMessageMove*)message)->positionX / this->caseSize;
			newPosX *= this->caseSize;
			newPosY = ((GameMessage::MouseMessageMove*)message)->positionY / this->caseSize;
			newPosY *= this->caseSize;
			this->composition->setX(newPosX);
			this->composition->setY(newPosY);
			break;
		case GameMessage::MOUSE_CLICK:
			if (((GameMessage::MouseMessageClick*)message)->leftClick) {
				GameTools::EditorManager::getInstance().createNewElement(this->composition->getX(), this->composition->getY());
			}
			if (((GameMessage::MouseMessageClick*)message)->rightClick) {
				GameTools::EditorManager::getInstance().removeElementByPosition(this->composition->getX(), this->composition->getY());
			}
			break;
		};
	}

}