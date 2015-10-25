#include "Camera.h"



void Camera::setX(int x)
{
	int width = this->cameraEndX - this->cameraStartX;
	this->cameraStartX = x;
	this->cameraEndX = this->cameraStartX + width;
}

void Camera::setY(int y)
{
	int height = this->cameraEndY - this->cameraStartY;
	this->cameraStartY = y;
	this->cameraEndY = this->cameraStartY + height;
}

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
