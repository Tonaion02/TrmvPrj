#pragma once

#include <array>
#include <vector>





#define MAX_W_MAP 100
#define MAX_H_MAP 100
#define MAX_Z_MAP 6





template<std::size_t n>
struct GraphicTileLayer
{
	std::array<short int, n> gTiles;
	std::vector<int> deepOfLayer;
};