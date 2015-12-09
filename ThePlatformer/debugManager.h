#pragma once

#include <iostream>
#include <string>
#include "ObjectFactory.h"
#include "Singleton.h"

namespace GameTools {
	class debugManager : public CSingletonStaticAlloc<debugManager>
	{
		friend class CSingletonStaticAlloc<debugManager>;

	public:
		enum DEBUG_TYPE
		{
			INFO,
			DEBUG_ERROR
		};
		~debugManager();

		bool isActivateText();
		void activateText();
		bool isActivateGraphic();
		void activateGraphic();
		void displayDebug(const std::string&, DEBUG_TYPE);
		void disableGraphic();
		void dAssert(std::string const &);

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


