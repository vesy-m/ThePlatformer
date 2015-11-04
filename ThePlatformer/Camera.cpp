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

void Camera::setResolution720p() {
	this->resolutionWidth = 1280;
	this->resolutionHeight = 720;
}

void Camera::setResolution1080p() {
	this->resolutionWidth = 1920;
	this->resolutionHeight = 1080;
}

Camera::Camera()
{
	this->resolutionWidth = 1280;
	this->resolutionHeight = 720;
	this->cameraStartX = 0;
	this->cameraEndX = this->resolutionWidth;
	this->cameraStartY = 0;
	this->cameraEndY = this->resolutionHeight;
}


Camera::~Camera()
{
}
