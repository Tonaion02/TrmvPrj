#pragma once

#include "ECS/Entity.h"





class LifeSystem
{
public:
	static void init();
	static void applyDamage();
	static void applyDamageToEntity(Entity e, float damage);
	static void checkIfIsDead();
	static void cleanDeadEntity();
	static void cleanInfo();
	static bool isDead(Entity e);
};