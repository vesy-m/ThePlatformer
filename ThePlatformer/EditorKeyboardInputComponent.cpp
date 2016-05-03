#include "EditorKeyboardInputComponent.h"
#include "SpriteComponent.h"
#include "FireMessage.h"
#include "EditorManager.h"

namespace GameComponents {

	EditorKeyboardInputComponent::EditorKeyboardInputComponent(GameObjects::BaseGameObject *object, bool saveRight) : InputComponent(object, false)
	{
		this->saveX = -32300;
		this->saveRight = saveRight;
		object->attachComponent(this);
	}


	EditorKeyboardInputComponent::~EditorKeyboardInputComponent()
	{
	}

	void EditorKeyboardInputComponent::UpdateInputState(sf::Event event, double dt)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::S && this->saveRight)
			{
				GameTools::EditorManager::getInstance().saveNewLevel();
			}
			if (event.key.code == sf::Keyboard::H) {
				if (this->saveX == -32300) {
					this->saveX = this->composition->getX();
					this->composition->setX(-500);
				}
				else {
					this->composition->setX(this->saveX);
					this->saveX = -32300;
				}
			}
			if (event.key.code == sf::Keyboard::Escape) {
				//GameTools::EditorManager::getInstance().clearLevel();
				GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/editor_level_menu.json");
			}
		}
	}

	void EditorKeyboardInputComponent::Init()
	{

	}

	void EditorKeyboardInputComponent::sendMessage(GameMessage::Message *message)
	{

	}
}
