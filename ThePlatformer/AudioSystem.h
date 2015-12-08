#pragma once
#ifndef _AUDIOSYSTEM_H_
#define _AUDIOSYSTEM_H_

#include <map>

#include "BaseSystem.h"
#include "Sound.h"
#include "SoundManager.h"
#include "debugManager.h"

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
		static bool				_pause;
		static bool				_pauseMenu;
	private:
		SoundMap				_sound;
		bool					isPaused;
		bool					_isAmbiance;
		bool					_isMenu;
	};
}

#endif // !_AUDIOSYSTEM_H_