#include "Sound.h"
#include <cassert>
#include <exception>

namespace GameTools
{
	CSound::CSound(std::string const &fileName, sf::SoundBuffer *sound)
		: _fileName(fileName)
	{
		_soundBuffer = new sf::SoundBuffer;
		if (!_soundBuffer->loadFromFile(fileName))
			debugManager::getInstance().dAssert("Path of the song does not exist");
		_sound = sf::Sound(*_soundBuffer);
	}

	CSound::~CSound() {}

	std::string const & CSound::getFileName() const { return _fileName; }

	void CSound::setLoop(bool loop)
	{
		_sound.setLoop(loop);
	}

	void CSound::setVolume(float volume)
	{
		_sound.setVolume(volume);
	}

	void CSound::play()
	{
		_sound.play();
	}

	void CSound::stop()
	{
		_sound.stop();
	}
}