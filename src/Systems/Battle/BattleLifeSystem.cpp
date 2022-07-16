#include "BattleLifeSystem.h"

//Including some components
#include "Components/Battle/ProjectileComponent.h"
#include "Components/Battle/PyshicBoxComponent.h"
//Including some components

//Including some systems
#include "Systems/Battle/ColliderSystem.h"
//Including some systems

//Including some Base ECS
#include "ECS/EntityManager.h"
#include "ECS/ECS.h"
//Including some Base ECS

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



void LifeSystem::applyDamageToEntity(Entity e, float damage)
{
	World* world = Game::get()->getWorld();

	LifeBarComponent* lifeBar = getCmpEntity(&world->mPoolLifeBarComponent, e);
	lifeBar->health -= damage;
}



template<typename Category, typename Category2>
void applyDamageForCategories(ComponentPool<Category>* pool, ComponentPool<Category2>* pool2)
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < pool->mNext; i++)
	{
		Entity e = pool->mDirectArray[i];

		if (isThereTypeCmp<ProjectileComponent>(e))
		{
			ProjectileComponent* proj = getCmpEntity(&world->mPoolProjectileComponent, e);
			RectColliderComponent* rect = getCmpEntity(&world->mPoolRectColliderComponent, e);
			TransformBattleComponent* transform = getCmpEntity(&world->mPoolTransformBattleComponent, e);

			for (unsigned int j = 0; j < pool2->mNext; j++)
			{
				Entity vs = pool2->mDirectArray[j];

				if (isThereTypeCmp<LifeBarComponent>(vs))
				{
					RectColliderComponent* rect2 = getCmpEntity(&world->mPoolRectColliderComponent, vs);
					TransformBattleComponent* transform2 = getCmpEntity(&world->mPoolTransformBattleComponent, vs);
					
					if (ColliderSystem::detectCollision(transform->pos, rect->dim, transform2->pos, rect2->dim))
					{
						LifeSystem::applyDamageToEntity(vs, proj->damage);
					}
				}
			}
		}
	}
}



void LifeSystem::applyDamage()
{
	World* world = Game::get()->getWorld();

	applyDamageForCategories(&world->mPoolPlayerBattleComponent, &world->mPoolEnemyBattleComponent);
	applyDamageForCategories(&world->mPoolEnemyBattleComponent, &world->mPoolPlayerBattleComponent);
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

		if (!LifeSystem::isDead(e2))
		{
			if (isThereTypeCmp<ProjectileComponent>(e2))
			{
				RectColliderComponent* rectColliderCmp2 = getCmpEntity(&world->mPoolRectColliderComponent, e);
				TransformBattleComponent* transformBattleCmp2 = getCmpEntity(&world->mPoolTransformBattleComponent, e2);

				if (ColliderSystem::detectCollision(transformBattleCmp->pos, rectColliderCmp->dim, transformBattleCmp2->pos, rectColliderCmp2->dim))
				{
					getCmpEntity(&world->mPoolLifeBarComponent, e)->health -= getCmpEntity(&world->mPoolProjectileComponent, e2)->damage;
				}
			}
		}
	}
}



void LifeSystem::checkIfIsDead()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolLifeBarComponent.mNext; i++)
	{
		Entity e = world->mPoolLifeBarComponent.mDirectArray[i];

		if (world->mPoolLifeBarComponent.mPackedArray[i].health <= 0.0f)
			//Add to entityToDelete
			world->entityToDelete.insert(e);
	}
}



void LifeSystem::cleanInfo()
{
	World* world = Game::get()->getWorld();

	world->entityToDelete.clear();
}



bool LifeSystem::isDead(Entity e)
{
	return Game::get()->getWorld()->entityToDelete.find(e) != Game::get()->getWorld()->entityToDelete.end();
}



void LifeSystem::cleanDeadEntity()
{
	World* world = Game::get()->getWorld();

	for (auto e : world->entityToDelete)
	{
		EntityManager::get().deleteEntity(e);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class LifeSystem
//-----------------------------------------------------------------------------------------------------------------------------------------