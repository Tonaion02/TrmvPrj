#pragma once

#include "ECS/Entity.h"





class EnemySystem
{
public:
	static void init();
	static void aiBaseEnemy();
protected:
	static void reversePath(Entity e);
};