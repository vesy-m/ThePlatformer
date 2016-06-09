#include "AudioComponent.h"
#include "JSONParser.h"

namespace GameComponents
{
	AudioComponent::AudioComponent(GameObjects::BaseGameObject *obj, std::string const &fileName) : BaseComponent(obj)
	{
		obj->attachComponent(this);
		_fileName = fileName;
		_currentSFX = "default";
		_fire = 0;
		_damage = 0;
	}

	AudioComponent::~AudioComponent()
	{
		SoundMap::iterator it = _sound.begin();

		for (; it != _sound.end(); ++it)
			if (it->second) it->second->stop();
	}

	void AudioComponent::Update(double dt) {}

	void AudioComponent::Init()
	{
		GameSystems::JSONParser parser(_fileName);
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
						std::string name;
						for (auto value : atr->value)
						{
							if (std::string("name").compare(value->key) == 0)
								name = value->value.toString();
							if (std::string("file").compare(value->key) == 0)
								_fileName = value->value.toString();
							if (std::string("volume").compare(value->key) == 0)
								_volume = (float)value->value.toNumber();
							if (std::string("loop").compare(value->key) == 0)
								_isLoop = value->value.toNumber() == 0 ? false : true;
						}
						_sound[name] = GameTools::CSoundManager::getInstance().getSound(_fileName);
						if (!_sound[name])
							GameTools::debugManager::getInstance().dAssert("Sound does not exist");
						_sound[name]->setLoop(_isLoop);
						_sound[name]->setVolume(_volume);
						if (std::string("ambiance").compare(name) == 0)
							sendMessage(new GameMessage::Message(GameMessage::PLAY_SOUND));
					}
				}
			}
		default:
			break;
		}
	}

	void AudioComponent::sendMessage(GameMessage::Message *message)
	{
		SoundMap::iterator it = _sound.begin();

		switch (message->id)
		{
		case GameMessage::LEFT:
			if (std::string("walk").compare(_currentSFX) != 0 && std::string("jump").compare(_currentSFX) != 0)
			{
				_currentSFX = "walk";
				if (_sound[_currentSFX])
					_sound[_currentSFX]->play();
			}
			break;
		case GameMessage::LEFT_RELEASED:
		{
			if (_sound["walk"])
				_sound["walk"]->stop();
			break;
		}
		case GameMessage::RIGHT:
			if (std::string("walk").compare(_currentSFX) != 0 && std::string("jump").compare(_currentSFX) != 0)
			{
				_currentSFX = "walk";
				if (_sound[_currentSFX])
					_sound[_currentSFX]->play();
			}
			break;
		case GameMessage::RIGHT_RELEASED:
		{
			if (_sound["walk"])
				_sound["walk"]->stop();
			break;
		}
		case GameMessage::JUMP:
 			if (std::string("jump").compare(_currentSFX) != 0)
			{
				_currentSFX = "jump";
				if (_sound[_currentSFX])
					_sound[_currentSFX]->play();
			}
			break;
		case GameMessage::STAND_ANIMATION:
			if (std::string("default").compare(_currentSFX) != 0)
			{
				if (_sound["jump"])
					_sound["jump"]->stop();
				_currentSFX = "default";
			}
			break;
		case GameMessage::DAMAGE:
			_currentSFX = "damage";
			_fire = 0;
			_damage = 150;
			if (_sound[_currentSFX])
				_sound[_currentSFX]->play();
			break;
		case GameMessage::PLAY_SOUND:
			if (_sound["ambiance"] && !GameTools::CSoundManager::getInstance().isMute())
				_sound["ambiance"]->play();
			break;
		case GameMessage::STOP_SOUND:
			if (_sound["ambiance"])
				_sound["ambiance"]->stop();
			for (; it != _sound.end(); ++it)
			{
				if (it->second)
					it->second->stop();
			}
			break;
		default:
			if (std::string("fire").compare(_currentSFX) == 0)
			{
				if (_fire <= 0)
				{
					if (_sound["fire"])
						_sound["fire"]->stop();
				}
				else
					--_fire;
			}
			if (std::string("damage").compare(_currentSFX) == 0)
			{
				if (_damage <= 0)
				{
					if (_sound["damage"])
						_sound["damage"]->stop();
				}
				else
					--_damage;
			}
			break;
		}
	}

	COMPONENT_TYPE AudioComponent::getType() const { return _type; }
}
