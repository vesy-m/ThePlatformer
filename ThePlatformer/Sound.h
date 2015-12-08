#pragma once

#include <SFML/Audio.hpp>
#include <string>

#include "debugManager.h"

namespace GameTools
{
	class					CSound
	{
	public:
		CSound(std::string const &, sf::SoundBuffer *);
		~CSound();

		std::string const	&getFileName() const;

		void				setLoop(bool);
		void				setVolume(float, bool save = true);

		float				getVolume() const;

		void				play();
		void				stop();

	private:
		std::string			_fileName;
		sf::Sound			_sound;
		sf::SoundBuffer		*_soundBuffer;
		float				_volume;
	};
}