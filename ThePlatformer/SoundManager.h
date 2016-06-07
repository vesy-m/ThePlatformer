#pragma once

#include <map>
#include <cassert>
#include <exception>

#include "Sound.h"
#include "AudioSystem.h"
#include "Singleton.h"

namespace GameTools
{
	class				CSoundManager : public CSingletonStaticAlloc<CSoundManager>
	{
		friend class	CSingletonStaticAlloc<CSoundManager>;

	public:
		CSound			*getSound(std::string const &);
		
		void			stopAllExceptAmbiance(std::string const, std::string const);
		void			muteAll();
		void			unmuteAll();
		void			muteMusic(std::string const ambiance, std::string const win);
		void			unmuteMusic(std::string const ambiance, std::string const win);
		bool			isMute() const;

	private:
		CSoundManager();
		~CSoundManager();
		CSoundManager(CSoundManager const&) = delete;
		void operator=(CSoundManager const&) = delete;

		void				loadSound(std::string const &);

		std::map<std::string, CSound>	_sound;
	};
}