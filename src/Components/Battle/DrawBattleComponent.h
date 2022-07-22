#pragma once

#include <string>

#include "utils/Math/Vector2i.h"





struct DrawBattleComponent
{
	int id;
	Vector2i dim;
	TileSet* tileSet = nullptr;
};