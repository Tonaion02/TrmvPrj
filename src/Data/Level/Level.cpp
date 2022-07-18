#include "Game.h"

//Including Enviroment
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including Data Manager
#include "World.h"
//Including Data Manager

//Including some physics Data Structures
#include "utils/Physic/GridSP.h"
//Including some physics Data Structures

#include "Data/Level/GraphicTileLayer.h"

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
	//level.dim = { 60, 60 };
	level.dim = { 40, 40 };
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
					level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = 54;
				}
			}
		}
	}

	for (int y = 0, z = 0, x = 30; y < level.dim.y; y++)
	{
		level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = 126;
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



	//Initialize the map of the Entity on the map
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
	//Initialize the map of the Entity on the map



	//Initialize the BattleCamp of the Level
	nameTexture = "data/buch-outdoor.png";
	level.battleCamp.texture = TextureHandler::get().getTexture(nameTexture);
	level.battleCamp.tileSet = *world->mTileSetHandler.getTileSet(nameTexture);

	level.battleCamp.dim = { 20, 20 };
	level.battleCamp.maxZ = 2;

	for (int z = 0; z < level.battleCamp.maxZ; z++)
	{
		for (int y = 0; y < level.battleCamp.dim.y; y++)
		{
			for (int x = 0; x < level.battleCamp.dim.x; x++)
			{
				level.battleCamp.graphicTileLayer.gTiles[z * level.battleCamp.dim.x * level.battleCamp.dim.y + y * level.battleCamp.dim.x + x] = -1;
			}
		}
	}

	for (int z = 0; z < level.battleCamp.maxZ; z++)
	{
		for (int y = 0; y < level.battleCamp.dim.y; y++)
		{
			for (int x = 0; x < level.battleCamp.dim.x; x++)
			{
				level.battleCamp.graphicTileLayer.gTiles[z * level.battleCamp.dim.x * level.battleCamp.dim.y + y * level.battleCamp.dim.x + x] = 13;
			}
		}
	}



	//Initialize the bound of the BattleCamp
	//Top
	level.battleCamp.boundCamp[0].start.x = 0;
	level.battleCamp.boundCamp[0].end.x = level.battleCamp.dim.x * level.battleCamp.tileSet.tileDim.x;
	level.battleCamp.boundCamp[0].start.y = (level.battleCamp.boundCamp[0].end.y = 0);
	level.battleCamp.boundCamp[0].orientation = 0;
	//Bottom
	level.battleCamp.boundCamp[1].start.x = 0;
	level.battleCamp.boundCamp[1].end.x = level.battleCamp.dim.x * level.battleCamp.tileSet.tileDim.x;
	level.battleCamp.boundCamp[1].start.y = (level.battleCamp.boundCamp[1].end.y = level.battleCamp.dim.y * level.battleCamp.tileSet.tileDim.y);
	level.battleCamp.boundCamp[1].orientation = 0;
	//Left
	level.battleCamp.boundCamp[2].start.x = (level.battleCamp.boundCamp[2].end.x = 0);
	level.battleCamp.boundCamp[2].start.y = 0;
	level.battleCamp.boundCamp[2].end.y = level.battleCamp.dim.y * level.battleCamp.tileSet.tileDim.y;
	level.battleCamp.boundCamp[2].orientation = 1;
	//Right
	level.battleCamp.boundCamp[3].start.x = (level.battleCamp.boundCamp[3].end.x = level.battleCamp.dim.x * level.battleCamp.tileSet.tileDim.x);
	level.battleCamp.boundCamp[3].start.y = 0;
	level.battleCamp.boundCamp[3].end.y = level.battleCamp.dim.y * level.battleCamp.tileSet.tileDim.y;
	level.battleCamp.boundCamp[3].orientation = 1;
	//Initialize the bound of the BattleCamp

	
	
	//Initialize the grid for spatial partition
	level.battleCamp.gridSP = GridSP(Vector2i(level.battleCamp.dim.x * level.tileSet.tileDim.x, level.battleCamp.dim.y * level.tileSet.tileDim.y), 
									 Vector2i(3 * level.tileSet.tileDim.x, 3 * level.tileSet.tileDim.y));
	//Initialize the grid for spatial partition

	//Initialize the BattleCamp of the Level
	
	return level;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Struct Level and function
//-----------------------------------------------------------------------------------------------------------------------------------------