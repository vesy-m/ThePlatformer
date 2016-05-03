#include "EditorManager.h"
#include "MouseComponent.h"
#include "EditorElementSelectorComponent.h"
#include "EditorCaseSelectorComponent.h"
#include "EditorKeyboardInputComponent.h"

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")
#include <il.h>
#include <SFML\OpenGL.hpp>
#include <sys/stat.h>

namespace GameTools {

	EditorManager::EditorManager()
	{
		//create GameObject Moving case by case follow mouse
		auto ret = new GameObjects::BaseGameObject();
		new GameComponents::SpriteComponent(ret, "./assets/levels_sprite/selection.png");
		new GameComponents::EditorKeyboardInputComponent(ret, true);
		new GameComponents::MouseComponent(ret, true);
		new GameComponents::EditorCaseSelectorComponent(ret, this->caseSelectionSize);
		ret->setX(0);
		ret->setY(0);
		ret->setScale(1.0f / (this->textureSize / this->caseSelectionSize));
		this->addObject(ret);

		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		int nbFileFind = 0;
		hFind = FindFirstFile("./assets/levels_sprite/element_sprite/*", &ffd);
		do
		{
			if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == false)
			{
				auto ret = new GameObjects::BaseGameObject();
				std::string pathFile = "./assets/levels_sprite/element_sprite/";
				pathFile += ffd.cFileName;
				new GameComponents::SpriteComponent(ret, pathFile);
				new GameComponents::EditorKeyboardInputComponent(ret, false);
				new GameComponents::MouseComponent(ret, false);
				new GameComponents::EditorElementSelectorComponent(ret, nbFileFind);

				ret->setX(0);
				ret->setY(this->midValue + (this->HWCase * nbFileFind));
				ret->setScale(2);
				ret->setDepth(1);

				this->addObject(ret);
				std::cout << "--" << ffd.cFileName << std::endl;
				this->listMaterial.push_back(pathFile);
				nbFileFind++;
			}
		} while (FindNextFile(hFind, &ffd) != 0);
		FindClose(hFind);
		this->maxSpace = (nbFileFind - 1) * 84;

		//create selectionSquare
		ret = new GameObjects::BaseGameObject();
		new GameComponents::SpriteComponent(ret, "./assets/levels_sprite/selection.png");
		new GameComponents::EditorKeyboardInputComponent(ret, false);
		ret->setX(0);
		ret->setY(318);
		ret->setScale(2);
		ret->setDepth(1);
		this->addObject(ret);

	}

	EditorManager::~EditorManager()
	{
	}

	void EditorManager::clearLevel() {
		this->editorLevelObjects.clear();
	}

	void EditorManager::LoadLevel(std::list<GameObjects::BaseGameObject*> &objects) {
		this->editorLevelObjects.clear();
		for each (GameObjects::BaseGameObject* obj in objects) {
			if (obj->getName() == "") {
				this->editorLevelObjects.push_front(obj);
				this->listElements[std::pair<int, int>(obj->getX(), obj->getY())].textureStr = ((GameComponents::SpriteComponent*)obj->getComponent(GameComponents::SPRITE))->fileName;
			}
		}
	}

	std::list<GameObjects::BaseGameObject*> & EditorManager::getObjects() {
		this->objectsToDisplay.clear();
		this->objectsToDisplay.insert(this->objectsToDisplay.end(), this->editorLevelObjects.begin(), this->editorLevelObjects.end());
		this->objectsToDisplay.insert(this->objectsToDisplay.end(), this->editorUtilityObjects.begin(), this->editorUtilityObjects.end());
		return this->objectsToDisplay;
	}

	void EditorManager::addObject(GameObjects::BaseGameObject* obj) {
		this->editorUtilityObjects.push_back(obj);
	}

	void EditorManager::setSelection(int pos)
	{
		this->positionSelected = pos;
	}

	GameObjects::BaseGameObject *EditorManager::getObjectByPosition(int posX, int posY) {
		for (GameObjects::BaseGameObject * obj : this->editorLevelObjects) {
			if (obj->getX() == posX && obj->getY() == posY) {
				return obj;
			}
		}
		return NULL;
	}

	void EditorManager::createNewElement(int posX, int posY)
	{
		//std::cout << "----------------------------------" << std::endl;
		//std::cout << this->editorLevelObjects.size() << std::endl;
		//std::cout << this->listElements.size() << std::endl;
		auto ret = getObjectByPosition(posX, posY);
		if (ret != NULL) {
			return;
		}
		ret = new GameObjects::BaseGameObject();
		new GameComponents::SpriteComponent(ret, this->listMaterial.at(this->positionSelected));
		ret->setX(posX);
		ret->setY(posY);
		ret->setDepth(3);
		ret->setScale(1.0f / (this->textureSize / this->caseSelectionSize));
		ret->Init();
		this->listElements[std::pair<int, int>(posX, posY)].textureStr = this->listMaterial.at(this->positionSelected);
		this->editorLevelObjects.push_front(ret);
		//std::cout << this->editorLevelObjects.size() << std::endl;
		//std::cout << this->listElements.size() << std::endl;
		//serializeMap();
	}

	void EditorManager::removeElementByPosition(int posX, int posY) {
		//std::cout << "----------------------------------" << std::endl;
		//std::cout << this->editorLevelObjects.size() << std::endl;
		//std::cout << this->listElements.size() << std::endl;
		for (GameObjects::BaseGameObject * obj : this->editorLevelObjects) {
			if (obj->getX() == posX && obj->getY() == posY) {
				this->editorLevelObjects.remove(obj);
				this->listElements.erase(std::pair<int, int>(posX, posY));
				//std::cout << this->editorLevelObjects.size() << std::endl;
				//std::cout << this->listElements.size() << std::endl;
				return;
			}
		}
	}

	void EditorManager::serializeMap(const std::string & fileName) {
		std::ofstream ss;
		ss.open(fileName, std::ofstream::out);
		ss << "{" << std::endl;
		ss << "  " << "\"objects\" : [" << std::endl;
		ss << "    " << "{" << std::endl;
		ss << "      " << "\"name\" : \"debugFps\"," << std::endl;
		ss << "      " << "\"x\" : 50," << std::endl;
		ss << "      " << "\"y\" : 50," << std::endl;
		ss << "      " << "\"depth\" : 3," << std::endl;
		ss << "      " << "\"fps\" : true" << std::endl;
		ss << "    " << "}," << std::endl;
		for (auto it = this->listElements.begin(); it != this->listElements.end(); ++it) {
			ss << "    " << "{" << std::endl;
			ss << "      " << "\"x\" : " << it->first.first << "," << std::endl;
			ss << "      " << "\"y\" : " << it->first.second << "," << std::endl;
			ss << "      " << "\"sprite\" : \"" << it->second.textureStr << "\"," << std::endl;
			ss << "      " << "\"scale\" : " << 1.0f / (this->textureSize / this->caseSelectionSize) << "," << std::endl;
			ss << "      " << "\"depth\" : 3," << std::endl;
			ss << "      " << "\"vector\" : \"square\"," << std::endl;
			ss << "      " << "\"boxcollider\" : true" << std::endl;
			ss << "    " << "}," << std::endl;
		}
		ss << "  " << "]" << std::endl;
		ss << "}" << std::endl;
		ss.close();
	}

	int EditorManager::getNumberOfNewLevel() {
		struct stat buffer;
		std::string pathLevelName = "./config/levels/level";
		int levelNumber = 1;
		std::string levelName = pathLevelName + std::to_string(levelNumber) + ".json";
		while (stat(levelName.c_str(), &buffer) == 0) {
			levelNumber++;
			levelName = pathLevelName + std::to_string(levelNumber) + ".json";
		}
		return levelNumber;
	}

	void EditorManager::takeScreenshot(const std::string & screenshotFile)
	{
		GLint iViewport[4];
		glGetIntegerv(GL_VIEWPORT, iViewport);
		int screenWidth = iViewport[0] + iViewport[2];
		int screenHeight = iViewport[1] + iViewport[3];
		std::cout << screenWidth << " " << screenHeight << std::endl;

		BYTE* pixels = new BYTE[3 * screenWidth * screenHeight];

		glReadPixels(0, 0, screenWidth, screenHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);

		int bytesToUsePerPixel = 3;
		int sizeOfByte = sizeof(unsigned char);

		int theSize = screenWidth * screenHeight * sizeOfByte * bytesToUsePerPixel;

		unsigned char * imData = (unsigned char*)malloc(theSize);

		for (int i = 0; i < theSize; i++)
		{
			imData[i] = pixels[i];
		}

		ILuint imageID = ilGenImage();

		ilBindImage(imageID);

		printf("New image!  width=%d,  height=%d,  bpp=%d\n", ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_BPP));

		printf("About to tex up your image\n");
		ilTexImage(screenWidth, screenHeight, 1, 3, IL_RGB, IL_UNSIGNED_BYTE, imData);

		printf("Your image was texxed\n");

		printf("Now width=%d,  height=%d,  bpp=%d\n", ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_BPP));

		ilEnable(IL_FILE_OVERWRITE);

		ilSave(IL_PNG, screenshotFile.c_str());
	}

	void EditorManager::saveNewLevel() {
		int levelNumber = getNumberOfNewLevel();
		std::string jsonLevelFile = "./config/levels/level" + std::to_string(levelNumber) + ".json";
		std::string pngLevelFile = "./assets/levels_preview/level" + std::to_string(levelNumber) + ".png";
		serializeMap(jsonLevelFile);
		takeScreenshot(pngLevelFile);
	}

}
