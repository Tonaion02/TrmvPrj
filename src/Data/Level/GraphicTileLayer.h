#pragma once

#include <array>





#define MAX_W_MAP 60
#define MAX_H_MAP 60
#define MAX_Z_MAP 3





struct GraphicTileLayer
{
	std::array<short int, MAX_W_MAP * MAX_H_MAP * MAX_Z_MAP> gTiles;
};