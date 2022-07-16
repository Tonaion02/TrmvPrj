#pragma once

#include <vector>
#include <set>

#include "ECS/Entity.h"
#include "utils/Math/Vector2i.h"





class GridSP
{
public:
	GridSP()
	{

	}

	GridSP(const Vector2i& dimCamp, const Vector2i& sizeCell)
		:sizeCell(sizeCell)
	{
		sizeCamp = Vector2i(dimCamp.x / sizeCell.x, dimCamp.y / sizeCell.y);

		for (int i = 0; i < sizeCamp.x * sizeCamp.y; i++)
			rawGrid.push_back(std::set<Entity>());
	}

	std::vector<std::set<Entity>> rawGrid;
	Vector2i sizeCamp;
	Vector2i sizeCell;
};