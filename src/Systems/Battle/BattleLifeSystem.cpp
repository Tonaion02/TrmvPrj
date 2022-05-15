#include "BattleLifeSystem.h"

//Including some components
#include "Components/Battle/ProjectileComponent.h"
#include "Components/Battle/PyshicBoxComponent.h"
//Including some components

//Including some systems
#include "Systems/Battle/ColliderSystem.h"
//Including some systems

//Including some context
#include "Game.h"
#include "World.h"
//Including some context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class LifeSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void LifeSystem::init()
{

}




template<typename TypeCmp>
void onCollisionForCategories(Entity e, ComponentPool<TypeCmp>* pool)
{
	World* world = Game::get()->getWorld();

	RectColliderComponent* rectColliderCmp = getCmpEntity(&world->mPoolRectColliderComponent, e);
	TransformBattleComponent* transformBattleCmp = getCmpEntity(&world->mPoolTransformBattleComponent, e);

	for (unsigned int j = 0; j < pool->mNext; j++)
	{
		Entity e2 = pool->mDirectArray[j];

		if (SignatureManager::get().isThereTypeCmp(e2, getIndexFromType<ProjectileComponent>()))
		{
			RectColliderComponent* rectColliderCmp2 = getCmpEntity(&world->mPoolRectColliderComponent, e);
			TransformBattleComponent* transformBattleCmp2 = getCmpEntity(&world->mPoolTransformBattleComponent, e2);

			if (ColliderSystem::detectCollision(transformBattleCmp->pos, rectColliderCmp->dim, transformBattleCmp2->pos, rectColliderCmp2->dim))
			{
				getCmpEntity(&world->mPoolLifeBarComponent, e)->health -= getCmpEntity(&world->mPoolProjectileComponent, e2)->damage;
				SDL_Log("damaged!");
			}
		}
	}
}



void LifeSystem::onCollision()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolLifeBarComponent.mNext; i++)
	{
		Entity e = world->mPoolLifeBarComponent.mDirectArray[i];

		onCollisionForCategories(e, &world->mPoolPlayerBattleComponent);
		onCollisionForCategories(e, &world->mPoolEnemyBattleComponent);
	}
}



void LifeSystem::checkIfIsDead()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolLifeBarComponent.mNext; i++)
	{
		Entity e = world->mPoolLifeBarComponent.mDirectArray[i];

		if (world->mPoolLifeBarComponent.mPackedArray[i].health <= 0.0f)
		{
			//destroy the dead entities
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class LifeSystem
//-----------------------------------------------------------------------------------------------------------------------------------------