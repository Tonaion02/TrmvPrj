#pragma once

#include <vector>
#include <set>

#include "ECS/Entity.h"
#include "utils/Math/Math.h"
#include "utils/Math/Math.h"





class GridSP
{
public:
	GridSP()
	{

	}

	GridSP(const Vector2i& dimCamp, const Vector2i& sizeCell)
		:sizeCell(sizeCell)
	{
		sizeCamp = Vector2i(static_cast<int>(roundf(dimCamp.x / static_cast<float>(sizeCell.x))),
			static_cast<int>(roundf(dimCamp.y / static_cast<float>(sizeCell.y))));

		for (int i = 0; i < sizeCamp.x * sizeCamp.y; i++)
			rawGrid.push_back(std::vector<Entity>());
	}

	std::vector<std::vector<Entity>> rawGrid;
	Vector2i sizeCamp;
	Vector2i sizeCell;
};