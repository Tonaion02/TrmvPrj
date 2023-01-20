#pragma once

#include "utils/Math/Vector2f.h"





class CameraSystem
{
public:
	static void init();
	static void updateCamera(const Vector2f& newPos);
	static void updateCameraZoom(float sign);
	static void onUpdateWindowSize();
	static void onUpdateZoom();
protected:

};