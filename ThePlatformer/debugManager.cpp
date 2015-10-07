#include "debugManager.h"

debugManager::debugManager()
{
	debugText = false;
	debugGraphic = true;
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



