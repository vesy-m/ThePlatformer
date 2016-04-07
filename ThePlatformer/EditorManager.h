#pragma once

#include <iostream>
#include <string>
#include "ObjectFactory.h"
#include "Singleton.h"


namespace GameTools {
	class EditorManager : public CSingletonStaticAlloc<EditorManager>
	{
		friend class CSingletonStaticAlloc<EditorManager>;

	public:
		~EditorManager();
		std::list<GameObjects::BaseGameObject*> & getObjects();
		void addObject(GameObjects::BaseGameObject* obj);
		int midValue = 318;
		int HWCase = 84;
		int maxSpace = 0;
		void setSelection(int pos);
		void createNewElement(int posX, int posY);
		GameObjects::BaseGameObject *EditorManager::getObjectByPosition(int posX, int posY);
		void removeElementByPosition(int posX, int posY);
		void serializeMap(const std::string & fileName);
		void takeScreenshot(const std::string & screenshotFile);
		int getNumberOfNewLevel();
		void saveNewLevel();


	private:
		class elementMap
		{
			public:
				std::string textureStr;
				bool IsSpawn;
		};
		EditorManager();
		EditorManager(EditorManager const&) = delete;
		void operator=(EditorManager const&) = delete;

		std::list<GameObjects::BaseGameObject*> objectsToDisplay;
		std::list<GameObjects::BaseGameObject*> editorLevelObjects;
		std::list<GameObjects::BaseGameObject*> editorUtilityObjects;
		int positionSelected = 0;
		std::vector<std::string> listMaterial;
		std::map<std::pair<int, int>, elementMap> listElements;

	};
}


