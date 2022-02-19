#pragma once

#include <array>





#define MAX_W_MAP 60
#define MAX_H_MAP 60
#define MAX_Z_MAP 3





template<std::size_t n>
struct GraphicTileLayer
{
	std::array<short int, n> gTiles;
};