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
}