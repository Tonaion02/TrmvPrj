#pragma once

#include <array>

#include "ECS/Entity.h"





//template<std::size_t WIDTH, std::size_t HEIGHT>
//std::array<unsigned int, 3> getIndexes(const GridSP<WIDTH, HEIGHT>& gridSP, const Vector2i& pos, const Vector2i& dim)
//{
//	std::array<unsigned int, 3> indexes;
//
//	Vector2i matrixPos = pos / gridSP.sizeCell;
//	unsigned int startCell = matrixPos.x + matrixPos.y * gridSP.sizeCamp.x;
//	Vector2i matrixEndPos = (pos + dim) / gridSP.sizeCell;
//	unsigned int w = matrixEndPos.x - matrixPos.x
//	unsigned int h = matrixEndPos.y - matrixPos.y;
//
//	indexes[0] = startCell;
//	indexes[1] = w;
//	indexes[2] = h;
//
//	return indexes;
//}
//
//
//
//template<std::size_t WIDTH, std::size_t HEIGHT>
//void registerEntity(Entity e, const GridSP<WIDTH, HEIGHT>& gridSP)
//{
//	World* world = Game::get()->getWorld();
//
//	TransformBattleComponent transformCMP = getCmpEntity(world->mPoolTransformBattleComponent, e);
//	RectColliderComponent rectColliderCMP = getCmpEntity(world->mPoolRectColliderComponent, e);
//
//	std::array<unsigned int, 3> limits = getIndexes(gridSP, transformCMP.pos, rectColliderCMP.dim);
//	
//	unsigned int index;
//	unsigned int h = 0;
//	unsigned int w;
//	//do
//	//{
//	//	w = 0;
//	//	do
//	//	{
//	//		index = limits[0] + w + h * gridSP.sizeCamp.x;
//	//		w++;
//	//	} while (w < limits[1]);
//	//	
//	//	h++;
//	//} while (h < limits[2]);
//
//	for (h = 0; h <= limits[2]; h++)
//	{
//		for (w = 0; w <= limits[1]; w++)
//		{
//			index = limits[0] + w + h * gridSP.sizeCamp.x;
//
//			gridSP.rawGrid[index].insert(e);
//		}
//	}
//}
//
//
//
//template<std::size_t WIDTH, std::size_t HEIGHT>
//void unRegisterEntity(Entity e, const GridSP<WIDTH, HEIGHT>& gridSP)
//{
//	World* world = Game::get()->getWorld();
//
//	TransformBattleComponent transformCMP = getCmpEntity(world->mPoolTransformBattleComponent, e);
//	RectColliderComponent rectColliderCMP = getCmpEntity(world->mPoolRectColliderComponent, e);
//
//	std::array<unsigned int, 3> limits = getIndexes(gridSP, transformCMP.pos, rectColliderCMP.dim);
//
//	unsigned int index;
//	unsigned int h = 0;
//	unsigned int w;
//
//	for (h = 0; h <= limits[2]; h++)
//	{
//		for (w = 0; w <= limits[1]; w++)
//		{
//			index = limits[0] + w + h * gridSP.sizeCamp.x;
//
//			gridSP.rawGrid[index].erase(e);
//		}
//	}
//}



class GridSP;
class Vector2i;

std::array<unsigned int, 3> getIndexes(const GridSP& gridSP, const Vector2i& pos, const Vector2i& dim);
void registerEntity(Entity e, GridSP& gridSP);
void unRegisterEntity(Entity e, GridSP& gridSP);