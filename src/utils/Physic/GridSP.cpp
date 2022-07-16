#include "GridSP.h"

#include "utils/Physic/DataGridSP.h"

#include "ECS/ECS.h"

#include "Game.h"
#include "World.h"





std::array<unsigned int, 3> getIndexes(const GridSP& gridSP, const Vector2i& pos, const Vector2i& dim)
{
	std::array<unsigned int, 3> indexes;

	Vector2i matrixPos = pos / gridSP.sizeCell;
	unsigned int startCell = matrixPos.x + matrixPos.y * gridSP.sizeCamp.x;
	Vector2i matrixEndPos = (pos + dim) / gridSP.sizeCell;
	unsigned int w = matrixEndPos.x - matrixPos.x;
	unsigned int h = matrixEndPos.y - matrixPos.y;

	indexes[0] = startCell;
	indexes[1] = w;
	indexes[2] = h;

	return indexes;
}



void registerEntity(Entity e, GridSP& gridSP)
{
	World* world = Game::get()->getWorld();

	TransformBattleComponent* transformCMP = getCmpEntity(&world->mPoolTransformBattleComponent, e);
	RectColliderComponent* rectColliderCMP = getCmpEntity(&world->mPoolRectColliderComponent, e);

	std::array<unsigned int, 3> limits = getIndexes(gridSP, transformCMP->pos, rectColliderCMP->dim);

	unsigned int index;
	unsigned int h = 0;
	unsigned int w;

	for (h = 0; h <= limits[2]; h++)
	{
		for (w = 0; w <= limits[1]; w++)
		{
			index = limits[0] + w + h * gridSP.sizeCamp.x;

			if(index < gridSP.rawGrid.size())
				gridSP.rawGrid[index].insert(e);
		}
	}
}



void unRegisterEntity(Entity e, GridSP& gridSP)
{
	World* world = Game::get()->getWorld();

	TransformBattleComponent* transformCMP = getCmpEntity(&world->mPoolTransformBattleComponent, e);
	RectColliderComponent* rectColliderCMP = getCmpEntity(&world->mPoolRectColliderComponent, e);

	std::array<unsigned int, 3> limits = getIndexes(gridSP, transformCMP->pos, rectColliderCMP->dim);

	unsigned int index;
	unsigned int h = 0;
	unsigned int w;

	for (h = 0; h <= limits[2]; h++)
	{
		for (w = 0; w <= limits[1]; w++)
		{
			index = limits[0] + w + h * gridSP.sizeCamp.x;
			
			if (index < gridSP.rawGrid.size())
				gridSP.rawGrid[index].erase(e);
		}
	}
}