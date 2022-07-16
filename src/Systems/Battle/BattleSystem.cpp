#include "Systems/Battle/BattleSystem.h"

//Including some Systems
#include "Systems/Battle/ColliderSystem.h"
//Including some Systems

//Including some Components
#include "Components/Battle/TransformBattleComponent.h"
#include "Components/Battle/RectColliderComponent.h"
//Including some Components

#include "ECS/ECS.h"

//Including some context
#include "Game.h"
#include "World.h"
//Including some context





void BattleSystem::init()
{

}



template<typename Category, typename Category2>
void updateBattleForCategories(ComponentPool<Category>* pool, ComponentPool<Category2>* poolVersus)
{
	World* world = Game::get()->getWorld();




	//for (unsigned int i = 0; i < pool->mNext; i++)
	//{
	//	Entity e = pool->mDirectArray[i];

	//	TransformBattleComponent* tbCmp = getCmpEntity(&world->mPoolTransformBattleComponent, e);
	//	RectColliderComponent* rcCmp = getCmpEntity(&world->mPoolRectColliderComponent, e);

	//	//It's an actor
	//	if (isThereTypeCmp<LifeBarComponent>(e) &&
	//		isThereTypeCmp<DamageComponent>(e))
	//	{
	//		LifeBarComponent* lbCmp = getCmpEntity(&world->mPoolLifeBarComponent, e);

	//		//Apply damage from various ECS class of elements
	//		for (unsigned int j = 0; j < poolVersus->mNext; j++)
	//		{
	//			Entity e2 = poolVersus->mDirectArray[j];

	//			TransformBattleComponent* tbCmp2 = getCmpEntity(&world->mPoolTransformBattleComponent, e2);
	//			RectColliderComponent* rcCmp2 = getCmpEntity(&world->mPoolRectColliderComponent, e2);

	//			if (isThereTypeCmp<ProjectileComponent>(e2))
	//			{
	//				if (ColliderSystem::detectCollision(tbCmp->pos, rcCmp->dim, tbCmp2->pos, rcCmp2->dim))
	//				{
	//					//Add call to lifeSystem
	//					lbCmp->health -= getCmpEntity(&world->mPoolProjectileComponent, e2)->damage;
	//					SDL_Log("Damaged entity: %d", (int)e);
	//				}
	//			}
	//		}
	//	}
	//	else if (isThereTypeCmp<ProjectileComponent>(e))
	//	{
	//		for (unsigned int j = 0; j < poolVersus->mNext; j++)
	//		{
	//			Entity e2 = poolVersus->mDirectArray[j];

	//			TransformBattleComponent* tbCmp2 = getCmpEntity(&world->mPoolTransformBattleComponent, e2);
	//			RectColliderComponent* rcCmp2 = getCmpEntity(&world->mPoolRectColliderComponent, e2);

	//			if (isThereTypeCmp<ControlledRectCollider>(e2))
	//			{
	//				if (ColliderSystem::detectCollision(tbCmp->pos, rcCmp->dim, tbCmp2->pos, rcCmp2->dim))
	//				{
	//					//Add to entity to delete
	//					world->entityToDelete.insert(e);
	//				}
	//			}
	//		}
	//	}
	//}
}



void BattleSystem::updateBattle()
{
	World* world = Game::get()->getWorld();
	updateBattleForCategories(&world->mPoolEnemyBattleComponent, &world->mPoolPlayerBattleComponent);
	updateBattleForCategories(&world->mPoolPlayerBattleComponent, &world->mPoolEnemyBattleComponent);
}