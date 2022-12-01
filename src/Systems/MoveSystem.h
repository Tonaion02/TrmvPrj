#pragma once

#include <vector>

#include "Misc/Direction.h"

#include "ECS/Entity.h"

#include "utils/Math/Vector2f.h"





class MoveSystem
{
public:
	static void move();
	static void startMove(Entity e, Direction direction);
	static void endMove(Entity e);
protected:
	static bool isValid(const Vector2f& pos, short int z);
};