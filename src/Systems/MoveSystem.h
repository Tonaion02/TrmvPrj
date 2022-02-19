#pragma once

#include <vector>

#include "ECS/System.h"
#include "ECS/Entity.h"





class MoveSystem : public System
{
public:
	static void move();
	static void startMove(Entity e);
	static void endMove(Entity e);
protected:
	static bool isValid(const class Vector2f& pos, short int z);
};