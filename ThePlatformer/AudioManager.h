#pragma once
#include <SFML\Audio.hpp>
#include <string>
#include <map>

class AudioManager
{
public:
	~AudioManager();
	static AudioManager& getInstance()
	{
		static AudioManager    instance;
		return instance;
	}
private:
	AudioManager();
	AudioManager(AudioManager const&) = delete;
	void operator=(AudioManager const&) = delete;

	std::map<std::string, sf::SoundBuffer> listSoundBuffer;
	std::map<std::string, sf::Sound> listSoundPlayer;
	std::map<std::string, sf::Music> listMusic;
};

