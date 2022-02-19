#include "TileSystem.h"

//Including Utils
#include "Math/Math.h"
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




//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TileSystem
//-----------------------------------------------------------------------------------------------------------------------------------------