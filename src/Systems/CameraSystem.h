#pragma once





class CameraSystem
{
public:
	static void init();
	static void updateCamera(const class Vector2f& newPos);
	static void updateCameraZoom(float sign);
	static void onUpdateWindowSize();
	static void onUpdateZoom();
protected:

};