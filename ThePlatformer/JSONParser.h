#pragma once

#include "gason.h"
#include <string>

namespace GameSystems {
	class JSONParser
	{
	public:
		JSONParser(const std::string&);
		~JSONParser();
		void initParse(const std::string&);
		JsonValue &getJSONValue(void);
	private:
		char			*readFile(const std::string&);
		JsonValue		m_value;
		JsonAllocator	m_allocator;
	};
}