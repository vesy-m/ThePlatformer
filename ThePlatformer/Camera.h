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
private:
	Camera();
	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;


};

