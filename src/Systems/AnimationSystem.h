#pragma once

#include "ECS/Entity.h"




class AnimationSystem
{
public:
	static void init();
	static void animate();
	static void startAnimation(Entity e);
};