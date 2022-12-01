#pragma once

#include <array>

#include "ECS/Entity.h"

#include "utils/Math/Vector2i.h"






class GridSP;

std::array<unsigned int, 3> getIndexes(const GridSP& gridSP, const Vector2i& pos, const Vector2i& dim);
void registerEntity(Entity e, GridSP& gridSP);
void unRegisterEntity(Entity e, GridSP& gridSP);
//void updateEntity(Entity e, GridSP& gridSP);