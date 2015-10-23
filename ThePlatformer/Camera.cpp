#include "Camera.h"



void Camera::setWidth(int width)
{
	this->cameraEndX = this->cameraStartX + width;
}

void Camera::setHeight(int height)
{
	this->cameraEndY = this->cameraStartY + height;
}

Camera::Camera()
{


}


Camera::~Camera()
{
}
