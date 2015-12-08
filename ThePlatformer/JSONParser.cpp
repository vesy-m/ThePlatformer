#include <fstream>
#include <sstream>
#include "gason.h"
#include "JSONParser.h"

namespace GameSystems {
	JSONParser::JSONParser(const std::string &filename = "")
	{
		if (filename != "") {
			this->initParse(filename);
		}
	}

	JSONParser::~JSONParser()
	{
	}

	void JSONParser::initParse(const std::string &filename) {
		char *jsonFile = readFile(filename), *endptr = NULL;
		if (jsonFile == NULL) {
			GameTools::debugManager::getInstance().dAssert("json file unreadable : " + filename);
		}
		int status = jsonParse(jsonFile, &endptr, &this->m_value, this->m_allocator);
		if (status != GameTools::JSON_OK) {
			GameTools::debugManager::getInstance().dAssert(GameTools::jsonStrError(status));
		}
	}

	GameTools::JsonValue &JSONParser::getJSONValue(void) {
		return this->m_value;
	}

	char *JSONParser::readFile(const std::string &filename) {
		std::string line;
		std::stringstream cacheFile = std::stringstream();
		std::ifstream myfile(filename);
		if (myfile.is_open())
		{
			while (getline(myfile, line)) cacheFile << line << '\n';
			myfile.close();
		}
		else return NULL;
		std::string tmp = cacheFile.str();
		char *cstr = new char[tmp.length() + 1];
		strcpy_s(cstr, tmp.length() + 1, tmp.c_str());
		return cstr;
	}
}