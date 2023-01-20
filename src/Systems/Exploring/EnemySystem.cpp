#include "EnemySystem.h"

#include "Data/Level/TileMap.h"

//Including some utils
#include "Misc/Direction.h"
//Including some utils

//Including Base ECS
#include "ECS/ECS.h"
//Including Base ECS

//Including components
#include "Components/Exploring/BaseEnemyComponent.h"
#include "Components/Exploring/MoveComponent.h"
//Including components

//Including systems
#include "Systems/Exploring/ActionSystem.h"
#include "Systems/Exploring/AnimationSystem.h"
#include "Systems/Exploring/MoveSystem.h"
//Including systems

//Including context
#include "Game.h"
#include "World.h"
//Including context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class EnemySystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void EnemySystem::init()
{
	World* world = Game::get()->getWorld();

	ComponentPool<BaseEnemyComponent>& BaseEnemyCmp = world->mPoolBaseEnemyComponent;
	ComponentPool<MoveComponent>& MoveCmp = world->mPoolMoveComponent;

	//Init all BaseEnemyComponent
	for (unsigned int i = 0; i < BaseEnemyCmp.mNext; i++)
	{
		BaseEnemyCmp.mPackedArray[i].alive = true;
		BaseEnemyCmp.mPackedArray[i].viewDistance = 3;
		BaseEnemyCmp.mPackedArray[i].currentStepPath = 0;
		MoveCmp.mPackedArray[i].lastDirection = BaseEnemyCmp.mPackedArray[i].path[0];
	}
	//Init all BaseEnemyComponent
}



void EnemySystem::aiBaseEnemy()
{
	World* world = Game::get()->getWorld();

	Level* currentLevel = &world->currentLevel;

	ComponentPool<BaseEnemyComponent>& BaseEnemyCmp = world->mPoolBaseEnemyComponent;
	ComponentPool<TransformComponent>& TransformCmp = world->mPoolTransformComponent;
	ComponentPool<ActionComponent>& ActionCmp = world->mPoolActionComponent;
	ComponentPool<MoveComponent>& MoveCmp = world->mPoolMoveComponent;

	for (unsigned int i = 0; i < BaseEnemyCmp.mNext; i++)
	{
		Entity e = world->mPoolBaseEnemyComponent.mDirectArray[i];

		Vector2i startPos = world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[e]].tileOccupied;
		int z = world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[e]].z;

		auto iter = std::find(world->battleEntities.begin(), world->battleEntities.end(), e);

		if (iter == world->battleEntities.end())
		{
			if (ActionSystem::isDoingNothing(e))
			{
				if (BaseEnemyCmp.mPackedArray[i].alive)
				{
					//Search the player beetween the range of view of the enemy
					bool found = false;

					for (int add = 1; add < BaseEnemyCmp.mPackedArray[i].viewDistance + 1; add++)
					{
						//Calculate pos to controll on the base of direction
						Vector2i pos = startPos;

						switch (MoveCmp.mPackedArray[MoveCmp.mReverseArray[e]].lastDirection)
						{
						case Up:
							pos.y -= add;
							break;
						case Down:
							pos.y += add;
							break;
						case Right:
							pos.x += add;
							break;
						case Left:
							pos.x -= add;
							break;
						default:
							break;
						}
						//Calculate pos to controll on the base of direction



						//Controll validity of the calculated pos
						if (pos.x < 0 || pos.y < 0 || pos.x >= currentLevel->dim.x || pos.y >= currentLevel->dim.y)
							break;
						//Controll validity of the calculated pos



						//Controll if in that pos there is player
						if (currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] == PlayerOccupier)
						{
							found = true;
							world->battleEntities.push_back(e);
							
							//Create entity for allerting animation
							Entity allertingEntity = createEntityId();

							//Init allertingEntity for the animation of allerting
							registerEntity(TransformCmp, allertingEntity);
							//TransformCmp->mPackedArray[TransformCmp->mReverseArray[allertingEntity]].pos = TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos;
							getCmpEntity(TransformCmp, allertingEntity).pos = getCmpEntity(TransformCmp, e).pos;
							//TransformCmp->mPackedArray[TransformCmp->mReverseArray[allertingEntity]].pos.y -= 1;
							getCmpEntity(TransformCmp, allertingEntity).pos.y -= 1;
							//TransformCmp->mPackedArray[TransformCmp->mReverseArray[allertingEntity]].z = TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].z;
							getCmpEntity(TransformCmp, allertingEntity).z = getCmpEntity(TransformCmp, e).z;
							registerEntity(world->mPoolDrawComponent, allertingEntity);
							//world->mPoolDrawComponent.mPackedArray[world->mPoolDrawComponent.mReverseArray[allertingEntity]].id = 117;
							getCmpEntity(world->mPoolDrawComponent, allertingEntity).id = 117;
							start(&world->delayTransictionToBattle);
							//Init allertingEntity for the animation of allerting

							world->allertingEntities.push_back(allertingEntity);

							//Register Entity to a group
							registerEntity(world->currentLevel.groupsEntities[getCmpEntity(world->mPoolTransformComponent, e).z], allertingEntity);
							//Register Entity to a group

							//Create entity for allerting animation

							break;
						}
						//Controll if in that pos there is player
					}
					//Search the player beetween the range of view of the enemy



					if (!found)
					{
						//Start an action if enemies not found the player
						ActionSystem::startAction(e, Actions::Walk);
						MoveSystem::startMove(e, BaseEnemyCmp.mPackedArray[i].path[BaseEnemyCmp.mPackedArray[i].currentStepPath]);
						AnimationSystem::startAnimation(e);
						BaseEnemyCmp.mPackedArray[i].currentStepPath++;


						//Controll if is terminated the path and reverse it
						if (BaseEnemyCmp.mPackedArray[i].currentStepPath == BaseEnemyCmp.mPackedArray[i].path.size())
							EnemySystem::reversePath(e);
						//Controll if is terminated the path and reverse it

						//Start an action if enemies not found the player
					}
				}
			}
		}
	}



	//If some enemy found an enemy
	if (!world->battleEntities.empty())
	{
		world->delayTransictionToBattle.timePassed += Game::get()->getDeltaTime();

		if (ActionSystem::isDoingNothing(world->player) && isEnd(world->delayTransictionToBattle))
		{
			//Before to startBattle try to delete allerting entities
			world->allertingEntities.clear();
			//Before to startBattle try to delete allerting entities


			//start battle
			Game::get()->startBattle();
		}
	}
	//If some enemy found an enemy
}



void EnemySystem::reversePath(Entity e)
{
	World* world = Game::get()->getWorld();

	ComponentPool<BaseEnemyComponent>& BaseEnemyCmp = world->mPoolBaseEnemyComponent;
	ComponentPool<MoveComponent>& MoveCmp = world->mPoolMoveComponent;

	std::vector<Direction> cpPath = BaseEnemyCmp.mPackedArray[BaseEnemyCmp.mReverseArray[e]].path;
	for (unsigned int i = 0; i < cpPath.size(); i++)
	{
		BaseEnemyCmp.mPackedArray[BaseEnemyCmp.mReverseArray[e]].path[i] = reverseDirection(cpPath[cpPath.size() - i - 1]);
	}

	BaseEnemyCmp.mPackedArray[BaseEnemyCmp.mReverseArray[e]].currentStepPath = 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class EnemySystem
//-----------------------------------------------------------------------------------------------------------------------------------------