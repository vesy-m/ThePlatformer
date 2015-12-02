#pragma once

#include "gason.h"
#include <string>
#include <iostream>

namespace GameSystems {
	class JSONParser
	{
	public:
		JSONParser(const std::string&);
		~JSONParser();
		void initParse(const std::string&);
		GameTools::JsonValue &getJSONValue(void);
	private:
		char			*readFile(const std::string&);
		GameTools::JsonValue		m_value;
		GameTools::JsonAllocator	m_allocator;
	};
}