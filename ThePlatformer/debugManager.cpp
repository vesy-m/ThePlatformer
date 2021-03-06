#include "debugManager.h"

namespace GameTools {
	debugManager::debugManager()
	{
		debugText = false;
		debugGraphic = false;
		rotateNum = -1;
		scaleNum = 0.1f;
	}

	debugManager::~debugManager()
	{
	}

	bool debugManager::isActivateText()
	{
		return debugText;
	}

	void debugManager::activateText()
	{
		debugText = true;
	}

	bool debugManager::isActivateGraphic()
	{
		return debugGraphic;
	}

	void debugManager::activateGraphic()
	{
		debugGraphic = true;
	}

	void debugManager::disableGraphic()
	{
		debugGraphic = false;
	}

	void debugManager::dAssert(std::string const &what)
	{
#ifdef _DEBUG
		assert(0, what.c_str());
#else
		throw std::exception(what.c_str());
#endif
	}

	void debugManager::displayDebug(const std::string &str, DEBUG_TYPE type)
	{
		switch (type)
		{
		case DEBUG_TYPE::DEBUG_ERROR:
			std::cout << "ERROR : " << str << std::endl;
			break;
		case DEBUG_TYPE::INFO:
			std::cout << "INFO : " << str << std::endl;
			break;
		default:
			std::cout << str << std::endl;
			break;
		}
	}
}
