#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(std::string & filename)
{
	std::string extension = getExtension(filename);
	if (std::string("json").compare(extension) == 0) {
		animated = true;
		loadAndParseJsonFile(filename);
	}
	else if (std::string("png").compare(extension) == 0) {
		animated = false;
		loadPngFile(filename);
	}

}

SpriteSheet::~SpriteSheet()
{

}


std::string SpriteSheet::getExtension(const std::string& filename) {
	return filename.substr(filename.find_last_of(".") + 1);
}

char	*SpriteSheet::readfile(const std::string & fileName)
{
	std::string line;
	std::stringstream cacheFile = std::stringstream();
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cacheFile << line << '\n';
		}
		myfile.close();
	}
	else {
		std::cout << "Unable to open file";
	}
	std::string tmp = cacheFile.str();
	char *cstr = new char[tmp.length() + 1];
	strcpy_s(cstr, tmp.length() + 1, tmp.c_str());
	return cstr;
}


int			SpriteSheet::parseSheetFile(JsonValue o) {
	switch (o.getTag()) {
		case JSON_OBJECT:
			for (auto i : o) {
				printf("%s = ", i->key);
				if (std::string("file").compare(i->key) == 0) {
					this->texture = TextureManager::getInstance().getTexture(i->value.toString());
				}
				if (std::string("anim").compare(i->key) == 0) {
					for (auto an : i->value) {
						SpriteAnimation anim = SpriteAnimation(an->value);
						this->anims[anim.getName()] = anim;
					}
				}
			
			}
			break;
	}
	return 0;
}

int			SpriteSheet::loadAndParseJsonFile(const std::string & filename)
{
	char	*jsonFile = readfile(filename);
	char	*endptr;
	JsonValue value;
	JsonAllocator allocator;
	int status = jsonParse(jsonFile, &endptr, &value, allocator);
	if (status != JSON_OK) {
		fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - jsonFile);
		exit(EXIT_FAILURE);
	}
	parseSheetFile(value);
	return 0;
}

int			SpriteSheet::loadPngFile(const std::string & filename)
{
	this->texture = TextureManager::getInstance().getTexture(filename);
	return 0;
}

bool		SpriteSheet::isAnimated()
{
	return animated;
}

const SpriteAnimation &SpriteSheet::getAnim(const std::string & animName) {
	return this->anims[animName];
}

Texture		*SpriteSheet::getTexture()
{
	return this->texture;
}
