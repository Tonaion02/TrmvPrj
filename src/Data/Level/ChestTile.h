#pragma once

#include <vector>

#include "utils/StringAndFile/XMLvariab.h"

#include "Data/Level/UniqueTile.h"





struct ChestTile : public UniqueTile
{
	int idItem;
	std::vector<int> idImages;
	int internalLayer;
	bool isOpened;

	ChestTile(XMLvariab& variab);
};