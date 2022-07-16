#include "PrecompiledHeaders.h"

#include "utils/Math/Math.h"

#include "Systems/Battle/ColliderSystem.h"

//Include some context
#include "Game.h"
#include "World.h"
//Include some context





void ColliderSystem::init()
{

}



bool ColliderSystem::detectCollisionX(int pos, int dim, int pos2, int dim2)
{
	return pos < pos2 + dim2 && pos + dim > pos2;
}



bool ColliderSystem::detectCollisionY(int pos, int dim, int pos2, int dim2)
{
	return pos + dim > pos2 && pos < pos2 + dim;
}



bool ColliderSystem::detectCollision(const Vector2f& pos, const Vector2i& dim, const Vector2f& pos2, const Vector2i& dim2)
{
	return ColliderSystem::detectCollisionX((int)pos.x, dim.x, (int)pos2.x, dim2.x) && ColliderSystem::detectCollisionX((int)pos.y, dim.y, (int)pos2.y, dim2.y);
}



bool ColliderSystem::detectCollision(const Line& line, const Vector2f& pos, const Vector2f& dim)
{
	//Orizzontal
	if (line.orientation == 0)
	{
		if (!(pos.y <= line.start.y && pos.y + dim.y >= line.start.y))
			return false;

		if (pos.x + dim.x < line.start.x || pos.x > line.end.x)
			return false;
	}
	//Vertical
	else
	{
		if (!(pos.x <= line.start.x && pos.x + dim.x >= line.start.x))
			return false;

		if (pos.y + dim.y < line.start.y || pos.y > line.end.y)
			return false;
	}

	return true;
}



void ColliderSystem::detectCollisions()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolRectColliderComponent.mNext; i++)
	{
		Entity e = world->mPoolRectColliderComponent.mDirectArray[i];

		Vector2f pos = world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos;
		Vector2i dim = world->mPoolRectColliderComponent.mPackedArray[i].dim;

		for (unsigned int j = i+1; j < world->mPoolRectColliderComponent.mNext; j++)
		{
			Entity e2 = world->mPoolRectColliderComponent.mDirectArray[j];

			if (detectCollision(pos, dim, world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e2]].pos, world->mPoolRectColliderComponent.mPackedArray[j].dim))
			{
				world->entitiesInCollisions.insert(e);
				world->entitiesInCollisions.insert(e2);
				world->collisions.push_back(std::pair<Entity, Entity>(e, e2));
			}
		}
	}
}



void ColliderSystem::collisionsResolution()
{

}



void ColliderSystem::collisionsInfoClear()
{
	World* world = Game::get()->getWorld();

	world->entitiesInCollisions.clear();
	world->collisions.clear();
}



Vector2f ColliderSystem::penetration(const Vector2f& pos, const Vector2i& dim, const Vector2f& pos2, const Vector2i& dim2)
{
	float x = std::max(pos.x, pos2.x);
	float y = std::max(pos.y, pos2.y);
	float x2 = std::min(pos.x + static_cast<float>(dim.x), pos2.x + static_cast<float>(dim.x));
	float y2 = std::min(pos.y + static_cast<float>(dim.y), pos2.y + static_cast<float>(dim.y));
	
	return Vector2f( x - x2, y - y2 );
}



Vector2f ColliderSystem::distance(const Vector2f& pos, const Vector2i& dim, const Vector2f& pos2, const Vector2i& dim2)
{
	float x = std::max(pos.x, pos2.x);
	float y = std::max(pos.y, pos2.y);
	float x2 = std::min(pos.x + static_cast<float>(dim.x), pos2.x + static_cast<float>(dim.x));
	float y2 = std::min(pos.y + static_cast<float>(dim.y), pos2.y + static_cast<float>(dim.y));

	return Vector2f(x - x2, y - y2);
}