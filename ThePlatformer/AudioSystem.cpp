#include "AudioSystem.h"
#include "JSONParser.h"

namespace GameSystems {

	bool AudioSystem::_menuVictory = false;
	bool AudioSystem::_pause = false;
	bool AudioSystem::_pauseMenu = false;
	bool AudioSystem::_muteAll = false;
	bool AudioSystem::_muteAmbiance = false;

	AudioSystem::AudioSystem()
	{
		isPaused = false;
		_isAmbiance = false;
		_isMenu = false;
		_isMuteAll = false;
		_isMuteAmbiance = false;
	}

	AudioSystem::~AudioSystem()
	{
	}

	int AudioSystem::Update(double dt, std::list<GameObjects::BaseGameObject*>&listObjects)
	{
		if (_pause && isPaused == false) {
			if (_sound["ambiance"])
				_sound["ambiance"]->stop();
			if (_sound["victory"])
				_sound["victory"]->stop();
			isPaused = true;
		}
		if (!_pause && isPaused) {
			if (!GameTools::CSoundManager::getInstance().isMute())
			{
				if (_sound["ambiance"] && _isAmbiance)
					_sound["ambiance"]->play();
				if (_sound["victory"] && !_isAmbiance)
					_sound["victory"]->play();
			}
			isPaused = false;
		}
		if (_pauseMenu && !_isMenu)
		{
			if (!GameTools::CSoundManager::getInstance().isMute())
			{
				GameTools::CSoundManager::getInstance().stopAllExceptAmbiance(_sound["ambiance"]->getFileName(), _sound["victory"]->getFileName());
				if (_sound["ambiance"])
					_sound["ambiance"]->setVolume(5, false);
				if (_sound["victory"])
					_sound["victory"]->setVolume(5, false);
			}
			_isMenu = true;
		}
		if (!_pauseMenu && _isMenu)
		{
			if (!GameTools::CSoundManager::getInstance().isMute())
			{
				GameTools::CSoundManager::getInstance().stopAllExceptAmbiance(_sound["ambiance"]->getFileName(), _sound["victory"]->getFileName());
				if (_sound["ambiance"])
					_sound["ambiance"]->setVolume(_sound["ambiance"]->getVolume());
				if (_sound["victory"])
					_sound["victory"]->setVolume(_sound["victory"]->getVolume());
			}
			_isMenu = false;
		}
		std::list<GameObjects::BaseGameObject*>::iterator it;
		for (it = listObjects.begin(); it != listObjects.end(); ++it)
		{
			GameComponents::BaseComponent *component = (*it)->getComponent(GameComponents::COMPONENT_TYPE::SOUND);
			if (component)
				component->Update(dt);
		}
		if (_muteAll && !_isMuteAll)
		{
			_isMuteAll = true;
			GameTools::CSoundManager::getInstance().muteAll();
		}
		else if (!_muteAll && _isMuteAll)
		{
			_isMuteAll = false;
			GameTools::CSoundManager::getInstance().unmuteAll();
		}
		if (_muteAmbiance && !_isMuteAmbiance)
		{
			_isMuteAmbiance = true;
			GameTools::CSoundManager::getInstance().muteMusic(_sound["ambiance"]->getFileName(), _sound["victory"]->getFileName());
		}
		else if (!_muteAmbiance && _isMuteAmbiance && !_muteAll)
		{
			_isMuteAmbiance = false;
			GameTools::CSoundManager::getInstance().unmuteMusic(_sound["ambiance"]->getFileName(), _sound["victory"]->getFileName());
		}
		return 0;
	}

	void AudioSystem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		bool isLoop = false;
		float volume = 0.0f;
		std::string name;
		std::string fileName;

		std::list<GameObjects::BaseGameObject*>::iterator it;
		for (it = listObjects.begin(); it != listObjects.end(); ++it)
		{
			GameComponents::BaseComponent *component = (*it)->getComponent(GameComponents::COMPONENT_TYPE::SOUND);
			if (component)
				component->Init();
		}

		GameSystems::JSONParser parser("./config/sound/Ambiance-SFX.json");
		GameTools::JsonValue value = parser.getJSONValue();
		switch (value.getTag())
		{
		case GameTools::JsonTag::JSON_OBJECT:
			for (auto i : value)
			{
				if (std::string("SFX").compare(i->key) == 0)
				{
					for (auto atr : i->value)
					{
						for (auto value : atr->value)
						{
							if (std::string("name").compare(value->key) == 0)
								name = value->value.toString();
							if (std::string("file").compare(value->key) == 0)
								fileName = value->value.toString();
							if (std::string("volume").compare(value->key) == 0)
								volume = (float)value->value.toNumber();
							if (std::string("loop").compare(value->key) == 0)
								isLoop = value->value.toNumber() == 0 ? false : true;
						}
						_sound[name] = GameTools::CSoundManager::getInstance().getSound(fileName);
						if (!_sound[name])
							GameTools::debugManager::getInstance().dAssert("Sound does not exist");
						_sound[name]->setLoop(isLoop);
						_sound[name]->setVolume(volume);
					}
				}
			}
		default:
			break;
		}
		if (_menuVictory)
		{
			if (!GameTools::CSoundManager::getInstance().isMute())
			{
				if (_sound["ambiance"])
					_sound["ambiance"]->stop();
				if (_sound["victory"])
					_sound["victory"]->play();
			}
			_menuVictory = false;
			_isAmbiance = false;
		}
		else if (!_isAmbiance)
		{
			if (!GameTools::CSoundManager::getInstance().isMute())
			{
				if (_sound["victory"])
					_sound["victory"]->stop();
				if (_sound["ambiance"])
					_sound["ambiance"]->play();
			}
			_isAmbiance = true;
		}
		if (_pauseMenu && !GameTools::CSoundManager::getInstance().isMute())
		{
			GameTools::CSoundManager::getInstance().stopAllExceptAmbiance(_sound["ambiance"]->getFileName(), _sound["victory"]->getFileName());
			if (_sound["ambiance"])
				_sound["ambiance"]->setVolume(5, false);
			if (_sound["victory"])
				_sound["victory"]->setVolume(5, false);
		}
		if (!_pauseMenu && !GameTools::CSoundManager::getInstance().isMute())
		{
			GameTools::CSoundManager::getInstance().stopAllExceptAmbiance(_sound["ambiance"]->getFileName(), _sound["victory"]->getFileName());
			if (_sound["ambiance"])
				_sound["ambiance"]->setVolume(_sound["ambiance"]->getVolume());
			if (_sound["victory"])
				_sound["victory"]->setVolume(_sound["victory"]->getVolume());
		}
		if (_muteAll)
			GameTools::CSoundManager::getInstance().muteAll();
		else if (!_muteAll && !_pauseMenu && _isMuteAll)
			GameTools::CSoundManager::getInstance().unmuteAll();
		if (_muteAmbiance)
			GameTools::CSoundManager::getInstance().muteMusic(_sound["ambiance"]->getFileName(), _sound["victory"]->getFileName());
		else if (!_muteAmbiance && !_muteAll && !_pauseMenu && _isMuteAmbiance)
			GameTools::CSoundManager::getInstance().unmuteMusic(_sound["ambiance"]->getFileName(), _sound["victory"]->getFileName());
	}

	void AudioSystem::SendAMessage() {}
}
