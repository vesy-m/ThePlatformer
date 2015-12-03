#pragma once
#ifndef _AUDIOSYSTEM_H_
#define _AUDIOSYSTEM_H_

#include <map>

#include "BaseSystem.h"
#include "Sound.h"
#include "SoundManager.h"

namespace GameSystems {
	typedef std::map<std::string, GameTools::CSound*> SoundMap;

	class AudioSystem : public BaseSystem
	{
	public:
		AudioSystem();
		~AudioSystem();

		int Update(double, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>&);
		void SendMessage();

		static bool				_menuVictory;
	private:
		SoundMap				_sound;
	};
}

#endif // !_AUDIOSYSTEM_H_