#pragma once

#include <vector>





enum LogicType
{
	NoneLogicType=-1,
	Ground,
	Wall,
	Sea
};




struct Tile
{
	short int logicType=-1;
	bool visible;
};



//struct TileMap
//{
//	std::array<Tile, MAX_W_MAP * MAX_H_MAP * MAX_Z_MAP> tiles;
//	std::array<int, MAX_W_MAP * MAX_H_MAP * MAX_Z_MAP> mappedUniqueTiles;
//	std::array<int, MAX_W_MAP * MAX_H_MAP * MAX_Z_MAP> mappedEntities;
//};

struct TileMap
{
	std::vector<Tile> tiles;
	std::vector<int> mappedUniqueTiles;
	std::vector<int> mappedEntities;
};