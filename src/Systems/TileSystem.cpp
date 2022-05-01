#include "TileSystem.h"

//Including Utils
#include "utils/Math/Math.h"
//Including Utils

//Including world
#include "Game.h"
#include "World.h"
//Including world





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TileSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
bool TileSystem::isWalkable(const Vector2i& pos, short int z)
{
	World* world = Game::get()->getWorld();

	switch (world->currentLevel.tileMap.tiles[z * world->currentLevel.dim.x * world->currentLevel.dim.y + 
											  pos.y * world->currentLevel.dim.x + 
									          pos.x].logicType)
	{
	case Wall:
	case Sea:
		return false;
	}

	return true;
}



void TileSystem::registerPos(const Vector2i& pos, short int z, Entity e)
{
	World* world = Game::get()->getWorld();
	Level* currentLevel = &world->currentLevel;

	//DA SOSTITUIRE
	if (e != world->player)
	{
		currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] = EntityOccupier::EnemyOccupier;
	}
	else
	{
		currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] = EntityOccupier::PlayerOccupier;
	}
}



void TileSystem::unRegisterPos(const Vector2i& pos, short int z)
{
	World* world = Game::get()->getWorld();
	Level* currentLevel = &world->currentLevel;

	currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] = NoneEntityOccupier;
}



bool TileSystem::isOccupied(const Vector2i& pos, short int z)
{
	World* world = Game::get()->getWorld();
	Level* currentLevel = &world->currentLevel;

	return currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] != NoneEntityOccupier;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TileSystem
//-----------------------------------------------------------------------------------------------------------------------------------------