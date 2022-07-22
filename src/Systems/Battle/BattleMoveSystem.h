#pragma once

#include "utils/Math/Math.h"
#include "ECS/Entity.h"





class BattleMoveSystem
{
public:
	static void init();
	static void freeMove();
	static void controlledMoves();
	static void followingMoves();
	static void applyForce(Entity e, const Vector2f& force);
	static void applyFriction(Entity e, float friction);
};