#pragma once

#include <vector>

#include "BaseGameObject.h"
#include "ObjectFactory.h"
#include "Sound.h"
#include "SoundManager.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	typedef std::map<std::string, GameTools::CSound*> SoundMap;

	class						AudioComponent : public BaseComponent
	{
		friend class			GameSystems::ObjectFactory;

	public:
		virtual					~AudioComponent();
		virtual void			Update(double);
		virtual void			Init();
		virtual void			sendMessage(GameMessage::Message*);

		virtual COMPONENT_TYPE	getType();

	private:
		AudioComponent(GameObjects::BaseGameObject*, std::string const &);

		const COMPONENT_TYPE	_type = COMPONENT_TYPE::SOUND;
		SoundMap				_sound;
		std::string				_fileName;
		std::string				_currentSFX;
		bool					_isLoop;
		float					_volume;
		unsigned int			_fire;
		unsigned int			_damage;
	};
}