#pragma once

#include "ECS/System.h"





class CameraSystem : public System
{
public:
	static void init();
	static void updateCamera();
	static void resetBaseInfo(); //Per ora unused
protected:

};