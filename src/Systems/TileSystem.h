#pragma once

#include "ECS/Entity.h"





class Vector2i;

class TileSystem
{
public:
	static bool isWalkable(const Vector2i& pos, short int z);
	static void registerPos(const Vector2i& pos, short int z, Entity e);
	static void unRegisterPos(const Vector2i& pos, short int z);
	static bool isOccupied(const Vector2i& pos, short int z);
protected:
};