#pragma once

#include <string>

#include "ECS/Entity.h"

#include "utils/Math/Vector2i.h"







class TileSystem
{
public:
	static bool isWalkable(const Vector2i& pos, short int z);
	static bool isInteractable(const Vector2i& pos, short int z);
	static bool isOccupied(const Vector2i& pos, short int z);

	static void registerPos(const Vector2i& pos, short int z, Entity e);
	static void unRegisterPos(const Vector2i& pos, short int z);
	
	static void interactReaction(const Vector2i& pos, short int z);

	static struct XMLvariab* uniqueTileWrapper(const std::string& path);
	static struct UniqueTile* createUniqueTile(struct XMLvariab* tileInfo);
protected:
};