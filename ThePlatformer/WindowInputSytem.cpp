#include "WindowInputSytem.h"



WindowInputSytem::WindowInputSytem()
{
}


WindowInputSytem::~WindowInputSytem()
{
}

void WindowInputSytem::Update(float dt, std::vector<BaseGameObject> listObjects)
{
	for each (BaseGameObject object in listObjects)
	{
		std::vector<BaseComponent*> componentList = object.getComponents("WINDOW");
	}
}

void WindowInputSytem::Init(void) 
{

}
void WindowInputSytem::SendMessage()
{

}