#pragma once
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
		void SendAMessage();

		static bool				_menuVictory;
		static bool				_pause;
		static bool				_pauseMenu;
		static bool				_muteAll;
		static bool				_muteAmbiance;
	private:
		SoundMap				_sound;
		bool					isPaused;
		bool					_isAmbiance;
		bool					_isMenu;
		bool					_isMuteAll;
		bool					_isMuteAmbiance;
	};
}