#pragma once

#include "ECS/Entity.h"





class LifeSystem
{
public:
	static void init();
	static void onCollision();
	static void checkIfIsDead();
	static void cleanDeadEntity();
	static void cleanInfo();
	static bool isDead(Entity e);
};