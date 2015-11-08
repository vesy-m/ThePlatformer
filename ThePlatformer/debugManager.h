#pragma once

#include <iostream>
#include <string>
#include "ObjectFactory.h"

namespace GameTools {
	class debugManager
	{
	public:
		enum DEBUG_TYPE
		{
			INFO,
			DEBUG_ERROR
		};
		~debugManager();
		static debugManager& getInstance()
		{
			static debugManager    instance;
			return instance;
		}

		bool isActivateText();
		void activateText();
		bool isActivateGraphic();
		void activateGraphic();
		void displayDebug(const std::string &, DEBUG_TYPE);
		void disableGraphic();
		int rotateNum;
		float scaleNum;

	private:
		debugManager();
		debugManager(debugManager const&) = delete;
		void operator=(debugManager const&) = delete;

		bool debugText;
		bool debugGraphic;
	};
}


