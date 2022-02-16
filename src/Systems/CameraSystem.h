#pragma once

#include "ECS/System.h"





class CameraSystem : public System
{
public:
	static void init();
	static void updateCamera();
	static void recalculateBaseInfo(); //Per ora unused
protected:

};