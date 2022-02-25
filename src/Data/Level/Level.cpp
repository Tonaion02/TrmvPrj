#include "Game.h"

//Including Enviroment
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including Data Manager
#include "World.h"
//Including Data Manager

#include "Data/Level/Level.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Struct Level and function
//-----------------------------------------------------------------------------------------------------------------------------------------
Level levelWrapper(const std::string& path)
{
	//INIT SOME BASE DATA
	Level level;
	World* world = Game::get()->getWorld();
	
	level.maxZ = 3;
	level.dim = { 60, 60 };
	//INIT SOME BASE DATA



	//INIT ID GRAPHICTILELAYER
	for (int z = 0; z < MAX_Z_MAP; z++)
	{
		for (int y = 0; y < MAX_H_MAP; y++)
		{
			for (int x = 0; x < MAX_W_MAP; x++)
			{
				level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = -1;
			}
		}
	}
	//INIT ID GRAPHICTILELAYER



	///FOR TESTING
	std::string nameTexture = "data/buch-outdoor.png";
	level.texture = TextureHandler::get().getTexture(nameTexture);
	level.tileSet = *world->mTileSetHandler.getTileSet(nameTexture);
	
	
	//SET ID TO DRAW
	for (int z = 0; z < MAX_Z_MAP; z++)
	{
		for (int y = 0; y < level.dim.y; y++)
		{
			for (int x = 0; x < level.dim.x; x++)
			{
				if (z == 2 || z == 1)
				{
					level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = -1;
				}
				else
				{
					level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = 0;
				}
			}
		}
	}

	for (int y = 0, z = 0, x = 30; y < level.dim.y; y++)
	{
		level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = 68;
	}
	//SET ID TO DRAW
	///FOR TESTING



	//Set logic id of tile
	level.tileMap.tiles.resize(level.maxZ * level.dim.y * level.dim.x);

	for (int z = 0; z < level.maxZ; z++)
	{
		for (int y = 0; y < level.dim.y; y++)
		{
			for (int x = 0; x < level.dim.x; x++)
			{
				level.tileMap.tiles[z * level.dim.x * level.dim.y + y * level.dim.x + x].logicType = static_cast<short int>(LogicType::NoneLogicType);
			}
		}
	}

	///FOR TESTING

	for (int z = 0; z < 1; z++)
	{
		for (int y = 0; y < level.dim.y; y++)
		{
			for (int x = 0; x < level.dim.x; x++)
			{
				level.tileMap.tiles[z * level.dim.x * level.dim.y + y * level.dim.x + x].logicType = static_cast<short int>(LogicType::Ground);
			}
		}
	}

	level.tileMap.tiles[0 * level.dim.x * level.dim.y + 0 * level.dim.x + 2].logicType = static_cast<short int>(LogicType::Wall);
	///FOR TESTING
	
	//Set logic id of tile

	level.tileMap.mappedEntities.resize(level.maxZ * level.dim.x * level.dim.y);
	for (int z = 0; z < level.maxZ; z++)
	{
		for (int y = 0; y < level.dim.y; y++)
		{
			for (int x = 0; x < level.dim.x; x++)
			{
				level.tileMap.mappedEntities[z * level.dim.x * level.dim.y + y * level.dim.x + x] = EntityOccupier::NoneEntityOccupier;
			}
		}
	}

	return level;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Struct Level and function
//-----------------------------------------------------------------------------------------------------------------------------------------