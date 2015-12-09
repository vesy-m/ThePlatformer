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