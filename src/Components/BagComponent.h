#pragma once

#include <array>

#include "Data/Items/Item.h"





struct BagComponent
{
	std::array<unsigned int, MAX_ITEMS> items;
};