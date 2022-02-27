#pragma once

#include "Data/Level/GraphicTileLayer.h"





#define MAX_W_CAMP 30
#define MAX_H_CAMP 30
#define MAX_Z_CAMP 2






struct BattleCamp
{
	GraphicTileLayer<MAX_W_CAMP * MAX_H_CAMP * MAX_Z_CAMP> gTiles;
};