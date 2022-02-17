#include "Game.h"

//Including Enviroment
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including Data Manager
#include "World.h"
//Including Data Manager

#include "Data/Level/Level.h"





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
		for (int y = 0; y < level.dim.y; y++)
		{
			for (int x = 0; x < level.dim.x; x++)
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
					level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = 68;
				}
				else
				{
					level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = 0;
				}
			}
		}
	}

	int z = 0,x = 59;
	//for (int y = 0; y < level.dim.y; y++)
	//{
	//	level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = 68;
	//}

	z = 0, x = 30;
	for (int y = 0; y < level.dim.y; y++)
	{
		level.graphicTileLayer.gTiles[z * level.dim.x * level.dim.y + y * level.dim.x + x] = 68;
	}
	//SET ID TO DRAW
	///FOR TESTING

	return level;
}