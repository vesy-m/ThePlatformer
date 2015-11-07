#pragma once
class Camera
{
public:
	~Camera();
	static Camera& getInstance()
	{
		static Camera    instance;
		return instance;
	}
	int cameraStartX;
	int cameraStartY;
	int cameraEndY;
	int cameraEndX;
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	int resolutionWidth;
	int resolutionHeight;
	void setResolution720p();
	void setResolution1080p();
private:
	Camera();
	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;
};

