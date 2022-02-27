#pragma once

#include <vector>

#include "Misc/Direction.h"

#include "ECS/System.h"
#include "ECS/Entity.h"





class MoveSystem : public System
{
public:
	static void move();
	static void startMove(Entity e, Direction direction);
	static void endMove(Entity e);
protected:
	static bool isValid(const class Vector2f& pos, short int z);
};