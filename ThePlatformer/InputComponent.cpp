#include "InputComponent.h"
#include "AutoPlayComponent.h"

namespace GameComponents {

	InputComponent::InputComponent(GameObjects::BaseGameObject *object, bool attachAsInput) : BaseComponent(object)
	{
		if (attachAsInput == true) {
			object->attachComponent(this);
		}
		this->duration = 500.0f;
		this->savedDt = 0.0f;
		this->maxElapsedTime = 2000.0f;
		this->attack_1 = 0;
		this->attack_2 = 0;
		this->attack_3 = 0;
		this->jump = 0;
	}

	InputComponent::~InputComponent()
	{
	}

	GameObjects::BaseGameObject * InputComponent::getComposition()
	{
		return this->composition;
	}

	void InputComponent::Update(double dt)
	{
		ExecuteCheatCode(IsCheatCodeActivated());

		this->attack_1 = (float) (this->attack_1 - dt > 0 ? this->attack_1 - dt : 0);
		this->attack_2 = (float) (this->attack_2 - dt > 0 ? this->attack_2 - dt : 0);
		this->attack_3 = (float)(this->attack_3 - dt > 0 ? this->attack_3 - dt : 0);
		this->jump = (float) (this->jump - dt > 0 ? this->jump - dt : 0);

		for (auto it = this->inputState.begin(); it != this->inputState.end(); ++it)
		{
			if (it->first == INPUT_TYPE::LEFT && it->second == true
				&& this->inputState.at(INPUT_TYPE::RIGHT) == false)
				getComposition()->sendMessage(new GameMessage::Message(GameMessage::LEFT));
			else if (it->first == INPUT_TYPE::RIGHT
				&& it->second == true && this->inputState.at(INPUT_TYPE::LEFT) == false)
				getComposition()->sendMessage(new GameMessage::Message(GameMessage::RIGHT));
			else if (it->first == INPUT_TYPE::JUMP && it->second == true)
			{
				if (jump == 0) {
					jump = this->composition->getJumpValue();
					getComposition()->sendMessage(new GameMessage::Message(GameMessage::JUMP));
				}
			}
			else if (it->first == INPUT_TYPE::DEBUG && it->second == true)
			{
				if (GameTools::debugManager::getInstance().isActivateGraphic()) GameTools::debugManager::getInstance().disableGraphic();
				else GameTools::debugManager::getInstance().activateGraphic();
				it->second = false;
			}
			else if (it->first == INPUT_TYPE::ROTATE_LEFT && it->second == true) getComposition()->sendMessage(new GameMessage::Message(GameMessage::ROTATE_LEFT));
			else if (it->first == INPUT_TYPE::ROTATE_RIGHT && it->second == true) getComposition()->sendMessage(new GameMessage::Message(GameMessage::ROTATE_RIGHT));
			else if (it->first == INPUT_TYPE::ATTACK3 && it->second == true && this->composition->getName().find("baseballPlayer") != std::string::npos) {
				if (attack_3 == 0)
					getComposition()->sendMessage(new GameMessage::Message(GameMessage::ATTACK3));
			}
		}
	}
	
	void InputComponent::ParseCheatCodeFile(std::string cheatCodeFilename)
	{
		std::string extension = cheatCodeFilename.substr(cheatCodeFilename.find_last_of(".") + 1);
		if (std::string("json").compare(extension) == 0) {
			GameSystems::JSONParser parser(cheatCodeFilename);
			GameTools::JsonValue jsonValue = parser.getJSONValue();
			switch (jsonValue.getTag()) {
			case GameTools::JSON_OBJECT:
				for (auto i : jsonValue) {
					printf("%s = ", i->key);
					CHEAT_CODE_TYPE cheatCodeType = (CHEAT_CODE_TYPE)std::stoi(i->key);
					std::vector<int> inputSequence;
					for (auto inputKey : i->value)
						inputSequence.push_back((int)inputKey->value.toNumber());
					cheatCodeMap.emplace(cheatCodeType, inputSequence);
				}
				break;
			}
		}
	}

	CHEAT_CODE_TYPE InputComponent::IsCheatCodeActivated()
	{
		if (savedMessage.size() == 0)
			return DEFAULT;
		for (auto cheatType : cheatCodeMap)
		{
			auto inputIt = cheatType.second.begin();
			for (auto savedMessageIt = savedMessage.begin(); savedMessageIt != savedMessage.end(); savedMessageIt++)
			{
				if (*savedMessageIt == *inputIt)
					inputIt++;
				else
					inputIt = cheatType.second.begin();

				if ((savedMessageIt + 1) == savedMessage.end() && inputIt == cheatType.second.end())
					return cheatType.first;
				else if (inputIt == cheatType.second.end())
					inputIt = cheatType.second.begin();
			}
		}
		return DEFAULT;
	}

	void InputComponent::ExecuteCheatCode(CHEAT_CODE_TYPE cheatType)
	{
		GameComponents::AutoPlayComponent *autoPlay = NULL;
		GameComponents::InputComponent *input = NULL;
		switch (cheatType)
		{
		case CHEAT_CODE_TYPE::I_WIN:
			std::cout << "CHEAT CODE ACTIVATED: I WIN" << std::endl;
			GameSystems::ObjectFactory::getInstance().winTheGame(this->composition->getName());
			savedMessage.clear();
			break;
		case CHEAT_CODE_TYPE::INVICIBLE:
			std::cout << "CHEAT CODE ACTIVATED: INVICIBLE" << std::endl;
			if (this->composition->getInvicible())
				this->composition->setInvicible(false);
			else
				this->composition->setInvicible(true);
			savedMessage.clear();
			break;
		case CHEAT_CODE_TYPE::LAUNCH_AUTO_PLAY:
			autoPlay = reinterpret_cast<GameComponents::AutoPlayComponent*>(getComposition()->getComponent(GameComponents::AUTO_PLAY));
			input = reinterpret_cast<GameComponents::InputComponent*>(getComposition()->getComponent(GameComponents::WINDOW));
			//autoPlay->SetActive(true);
			input->SetActive(false);
		default:
			break;
		}
	}

	void InputComponent::setDuration(float duration)
	{
		this->duration = duration;
	}
	float InputComponent::getDuration()
	{
		return this->duration;
	}
	void InputComponent::setSavedDt(float savedDt)
	{
		this->savedDt = savedDt;
	}
	float InputComponent::getSavedDt()
	{
		return this->savedDt;
	}
	float InputComponent::getMaxElapsedTime()
	{
		return this->maxElapsedTime;
	}
}
