#include "SoundManager.h"

namespace GameTools
{
	CSoundManager::CSoundManager()
	{
		_sound = std::map<std::string, CSound>();
	}

	CSoundManager::~CSoundManager() {}

	void CSoundManager::loadSound(std::string const &fileName)
	{
		std::map<std::string, CSound>::iterator it;

		it = _sound.find(fileName);
		if (it != _sound.end())
			return;
		_sound.insert(std::pair<std::string, CSound>(fileName, CSound(fileName, NULL)));
	}

	CSound		*CSoundManager::getSound(std::string const &fileName)
	{
		try {
			return &_sound.at(fileName);
		}
		catch (const std::out_of_range &)
		{
			loadSound(fileName);
		}
		return &_sound.at(fileName);
	}

	void CSoundManager::stopAllExceptAmbiance(std::string const ambiance, std::string const victory)
	{
		std::map<std::string, CSound>::iterator it;

		for (it = _sound.begin(); it != _sound.end(); ++it)
		{
			if (it->first != victory && it->first != ambiance)
				it->second.stop();
		}
	}

	void CSoundManager::muteAll()
	{
		std::map<std::string, CSound>::iterator it;

		for (it = _sound.begin(); it != _sound.end(); ++it)
			it->second.setVolume(0.0f, false);
	}

	void CSoundManager::unmuteAll()
	{
		std::map<std::string, CSound>::iterator it;

		for (it = _sound.begin(); it != _sound.end(); ++it)
			it->second.setVolume(it->second.getVolume(), false);
	}
	void CSoundManager::muteMusic(std::string const ambiance)
	{
		std::map<std::string, CSound>::iterator it;

		for (it = _sound.begin(); it != _sound.end(); ++it)
		{
			if (it->first == ambiance)
				it->second.setVolume(0.0f, false);
		}
	}

	void CSoundManager::unmuteMusic(std::string const ambiance)
	{
		std::map<std::string, CSound>::iterator it;

		for (it = _sound.begin(); it != _sound.end(); ++it)
		{
			if (it->first == ambiance)
				it->second.setVolume(it->second.getVolume(), false);
		}
	}
	
	bool CSoundManager::isMute() const
	{
		if (GameSystems::AudioSystem::_muteAll || GameSystems::AudioSystem::_muteAmbiance)
			return true;
		return false;
	}
}