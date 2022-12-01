#include "Systems/Battle/ProjectileSystem.h"

#include "Systems/Battle/ColliderSystem.h"

#include "Components/Battle/ControlledRectCollider.h"

#include "ECS/ECS.h"

//Including some Phyiscs elements
#include "utils/Physic/GridSP.h"
//Including some Phyiscs elements

//Including context
#include "World.h"
#include "Game.h"
//Including context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ProjectileSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void ProjectileSystem::init()
{

}



template<typename Category>
bool checkIfIsDeadProjectileForCategory(Entity e)
{
	World* world = Game::get()->getWorld();

	TransformBattleComponent& transform = getCmpEntity(world->mPoolTransformBattleComponent, e);
	RectColliderComponent& rect = getCmpEntity(world->mPoolRectColliderComponent, e);

	std::array<unsigned int, 3> indexes = getIndexes(world->currentLevel.battleCamp.gridSP, transform.pos, rect.dim);

	unsigned int i;
	for (unsigned int h = 0; h <= indexes[2]; h++)
	{
		i = indexes[0] + h * world->currentLevel.battleCamp.gridSP.sizeCamp.x;
		for (unsigned int w = 0; w <= indexes[1]; w++,i++)
		{
			std::vector<Entity>::iterator iter;

			if (i < world->currentLevel.battleCamp.gridSP.rawGrid.size())
			{
				for (iter = world->currentLevel.battleCamp.gridSP.rawGrid[i].begin(); iter != world->currentLevel.battleCamp.gridSP.rawGrid[i].end(); iter++)
				{
					if (*iter != e)
					{
						if (isThereTypeCmp<Category>(*iter) && isThereTypeCmp<RectColliderComponent>(*iter))
						{
							TransformBattleComponent& transform2 = getCmpEntity(world->mPoolTransformBattleComponent, *iter);
							RectColliderComponent& rect2 = getCmpEntity(world->mPoolRectColliderComponent, *iter);

							if (ColliderSystem::detectCollision(transform.pos, rect.dim, transform2.pos, rect2.dim))
							{
								world->entityToDelete.insert(e);
								unRegisterEntity(e, world->currentLevel.battleCamp.gridSP);
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}



void ProjectileSystem::checkIfIsDeadProjectile()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolProjectileComponent.mNext; i++)
	{
		Entity entity = world->mPoolProjectileComponent.mDirectArray[i];

		if (isThereTypeCmp<PlayerBattleComponent>(entity))
			checkIfIsDeadProjectileForCategory<EnemyBattleComponent>(entity);
		else if (isThereTypeCmp<EnemyBattleComponent>(entity))
			checkIfIsDeadProjectileForCategory<PlayerBattleComponent>(entity);

		for (unsigned int j = 0; j < world->currentLevel.battleCamp.boundCamp.size(); j++)
		{
			if (ColliderSystem::detectCollision(world->currentLevel.battleCamp.boundCamp[j],
				getCmpEntity(world->mPoolTransformBattleComponent, entity).pos,
				getCmpEntity(world->mPoolRectColliderComponent, entity).dim))
			{
				world->entityToDelete.insert(entity);
				unRegisterEntity(entity, world->currentLevel.battleCamp.gridSP);
				break;
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ProjectileSystem
//-----------------------------------------------------------------------------------------------------------------------------------------