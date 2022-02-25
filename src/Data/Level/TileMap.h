#pragma once

#include <vector>





enum LogicType
{
	NoneLogicType=-1,
	Ground,
	Wall,
	Sea
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





//struct TileMap
//{
//	std::vector<Tile> tiles;
//	std::vector<int> mappedUniqueTiles;
//	std::vector<int> mappedEntities;
//};
struct TileMap
{
	std::vector<Tile> tiles;
	std::vector<int> mappedEntities;
};