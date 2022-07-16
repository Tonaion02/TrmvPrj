#pragma once

#include "utils/Math/Math.h"

#include "utils/Physic/Line.h"

#include "ECS/Entity.h"





class ColliderSystem
{
public:
	static void init();
	static bool detectCollisionX(int pos, int dim, int pos2, int dim2);
	static bool detectCollisionY(int pos, int dim, int pos2, int dim2);
	static bool detectCollision(const Vector2f& pos, const Vector2i& dim, const Vector2f& pos2, const Vector2i& dim2);
	static void detectCollisions();
	static bool detectCollision(const Line& line, const Vector2f& pos, const Vector2f& dim);
	static void collisionsResolution();
	static void collisionsInfoClear();
	static Vector2f penetration(const Vector2f& pos, const Vector2i& dim, const Vector2f& pos2, const Vector2i& dim2);
	static Vector2f distance(const Vector2f& pos, const Vector2i& dim, const Vector2f& pos2, const Vector2i& dim2);
};