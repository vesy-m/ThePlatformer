#include "AudioSystem.h"
#include "JSONParser.h"

namespace GameSystems {

	bool AudioSystem::_menuVictory = false;

	AudioSystem::AudioSystem()
	{
	}


	AudioSystem::~AudioSystem()
	{
	}

	int AudioSystem::Update(double dt, std::list<GameObjects::BaseGameObject*>&listObjects)
	{
		std::list<GameObjects::BaseGameObject*>::iterator it;
		for (it = listObjects.begin(); it != listObjects.end(); ++it)
		{
			GameComponents::BaseComponent *component = (*it)->getComponent(GameComponents::COMPONENT_TYPE::SOUND);
			if (component)
				component->Update(dt);
		}
		return 0;
	}

	void AudioSystem::Init(std::list<GameObjects::BaseGameObject*>& listObjects)
	{
		bool isLoop = false;
		unsigned int volume = 0;
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
								volume = value->value.toNumber();
							if (std::string("loop").compare(value->key) == 0)
								isLoop = value->value.toNumber();
						}
						_sound[name] = GameTools::CSoundManager::getInstance().getSound(fileName);
						assert(_sound[name] != NULL);
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
			if (_sound["ambiance"])
				_sound["ambiance"]->stop();
			if (_sound["victory"])
				_sound["victory"]->play();
			_menuVictory = false;
		}
		else
		{
			if (_sound["victory"])
				_sound["victory"]->stop();
			if (_sound["ambiance"])
				_sound["ambiance"]->play();
		}
	}

	void AudioSystem::SendMessage() {}
}
