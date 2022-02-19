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





struct TileMap
{
	std::vector<Tile> tiles;
	std::vector<int> mappedUniqueTiles;
	std::vector<int> mappedEntities;
};