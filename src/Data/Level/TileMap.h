#pragma once

#include <vector>

//Include all the Tile
#include "Data/Level/UniqueTile.h"
#include "Data/Level/ChestTile.h"
//Include all the Tile





enum LogicType
{
	NoneLogicType=-1,
	Ground,
	Wall,
	Sea,
	Chest
};


enum EntityOccupier
{
	NoneEntityOccupier = -1,
	PlayerOccupier,
	EnemyOccupier
};





struct Tile
{
	short int logicType=-1;
	bool visible;
};






struct TileMap
{
	std::vector<Tile> tiles;
	std::vector<int> mappedEntities;

	std::vector<struct UniqueTile*> uniqueTiles;
};