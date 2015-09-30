#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(std::string & jsonfileName)
{
	char	*jsonFile = readfile(jsonfileName);
	char *endptr;
	JsonValue value;
	JsonAllocator allocator;
	int status = jsonParse(jsonFile, &endptr, &value, allocator);
	if (status != JSON_OK) {
		fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - jsonFile);
		exit(EXIT_FAILURE);
	}
	double sum = sum_and_print(value);
	printf("sum of all numbers: %g\n", sum);
}

SpriteSheet::SpriteSheet()
{
}

SpriteSheet::~SpriteSheet()
{

}


char	*SpriteSheet::readfile(std::string & jsonfileName)
{
	std::string line;
	std::stringstream cacheFile = std::stringstream();
	std::ifstream myfile(jsonfileName);
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


double SpriteSheet::sum_and_print(JsonValue o) {
	double sum = 0;
	switch (o.getTag()) {
		case JSON_OBJECT:
			for (auto i : o) {
				printf("%s = ", i->key);
				if (std::string("name").compare(i->key) == 0) {
					this->name = i->value.toString();
				}
				if (std::string("file").compare(i->key) == 0) {
					loadTexture(i->value.toString());
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
	return sum;
}

void SpriteSheet::loadTexture(const std::string filename)
{
	ILboolean success;
	unsigned int imageID;

	// init DevIL. This needs to be done only once per application
	ilInit();
	// generate an image name
	ilGenImages(1, &imageID);
	// bind it
	ilBindImage(imageID);
	// match image origin to OpenGL’s
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	// load  the image
	success = ilLoadImage((ILstring)filename.c_str());
	// check to see if everything went OK
	if (!success) {
		std::cout << "file charged" << std::endl;
	}
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);


	/* Create and load textures to OpenGL */
	glGenTextures(1, &textureSpriteSheetID); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, textureSpriteSheetID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		ilGetData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	widthPixel = ilGetInteger(IL_IMAGE_WIDTH);
	heightPixel = ilGetInteger(IL_IMAGE_HEIGHT);
}