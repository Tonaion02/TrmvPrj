#pragma once

#include "ECS/System.h"





class CameraSystem : public System
{
public:
	static void init();
	static void updateCamera();
	static void updateCameraZoom(float sign);
	static void onUpdateWindowSize();
	static void onUpdateZoom();
protected:

};