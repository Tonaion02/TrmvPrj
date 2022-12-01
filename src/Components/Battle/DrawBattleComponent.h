#pragma once

#include <string>

#include "utils/Math/Math.h"





struct DrawBattleComponent
{
	int id;
	Vector2i dim;
	TileSet* tileSet = nullptr;
};