#include "PrecompiledHeaders.h"

//Including some Systems
#include "Systems/Battle/BattleMoveSystem.h"
#include "Systems/Battle/ColliderSystem.h"
//Including some Systems

#include "ECS/ECS.h"

//Including some Matematics elements
#include "utils/Math/Math.h"
//Including some Matematics elements

//Including some Physics elements
#include "utils/Physic/GridSP.h"
//Including some Physics elements

//Including some context
#include "World.h"
#include "Game.h"
//Including some context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class BattleMoveSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void BattleMoveSystem::init()
{

}



void BattleMoveSystem::applyForce(Entity e, const Vector2f& force)
{
	World* world = Game::get()->getWorld();

	Vector2f v = force / world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].mass;
	world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v += v;
}



void BattleMoveSystem::applyFriction(Entity e, float friction = 1.0f)
{
	World* world = Game::get()->getWorld();

	getCmpEntity(world->mPoolPhysicBoxComponent, e).v.x = 0.0f;
	getCmpEntity(world->mPoolPhysicBoxComponent, e).v.y = 0.0f;
}



void BattleMoveSystem::freeMove()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolFreeRectColliderComponent.mNext; i++)
	{
		Entity e = world->mPoolFreeRectColliderComponent.mDirectArray[i];

		unRegisterEntity(e, world->currentLevel.battleCamp.gridSP);

		getCmpEntity(world->mPoolTransformBattleComponent, e).pos += getCmpEntity(world->mPoolPhysicBoxComponent, e).v * Game::get()->getDeltaTime();

		registerEntity(e, world->currentLevel.battleCamp.gridSP);
	}
}



void BattleMoveSystem::controlledMoves()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolControlledRectColliderComponent.mNext; i++)
	{
		Entity e = world->mPoolControlledRectColliderComponent.mDirectArray[i];

		unRegisterEntity(e, world->currentLevel.battleCamp.gridSP);

		getCmpEntity(world->mPoolTransformBattleComponent, e).pos += getCmpEntity(world->mPoolPhysicBoxComponent, e).v * Game::get()->getDeltaTime();

		TransformBattleComponent& transform= getCmpEntity(world->mPoolTransformBattleComponent, e);
		RectColliderComponent& rect = getCmpEntity(world->mPoolRectColliderComponent, e);

		std::array<unsigned int, 3> indexes = getIndexes(world->currentLevel.battleCamp.gridSP, transform.pos, rect.dim);

		unsigned int index;
		for (unsigned int h = 0; h <= indexes[2]; h++)
		{
			index = indexes[0] + h * world->currentLevel.battleCamp.gridSP.sizeCamp.x;

			for (unsigned int w = 0; w <= indexes[1]; w++, index++)
			{
				std::vector<Entity>::iterator iter;

				if(index < world->currentLevel.battleCamp.gridSP.rawGrid.size())
					for (iter = world->currentLevel.battleCamp.gridSP.rawGrid[index].begin(); iter != world->currentLevel.battleCamp.gridSP.rawGrid[index].end(); iter++)
					{
						if (*iter != e)
						{
							if (isThereTypeCmp<ControlledRectCollider>(*iter))
							{
								TransformBattleComponent& transform2 = getCmpEntity(world->mPoolTransformBattleComponent, *iter);
								RectColliderComponent& rect2 = getCmpEntity(world->mPoolRectColliderComponent, *iter);

								if (ColliderSystem::detectCollision(transform.pos, rect.dim, transform2.pos, rect2.dim))
								{
									Vector2f penetration = ColliderSystem::penetration(transform.pos, rect.dim, transform2.pos, rect2.dim);

									Vector2i signs;
									if (transform.pos.x > transform2.pos.x)
										signs.x = -1;
									else
										signs.x = 1;

									if (transform.pos.y > transform2.pos.y)
										signs.y = -1;
									else
										signs.y = 1;

									if (penetration.x >= penetration.y)
									{
										transform.pos.x += signs.x * penetration.x;
									}
									else
									{
										transform.pos.y += signs.y * penetration.y;
									}

									getCmpEntity(world->mPoolPhysicBoxComponent, e).v = { 0.0f, 0.0f };
								}
							}
						}
					}
			}
		}

		registerEntity(e, world->currentLevel.battleCamp.gridSP);
	}
}



void BattleMoveSystem::followingMoves()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolFollowingComponent.mNext; i++)
	{
		Entity e = world->mPoolFollowingComponent.mDirectArray[i];

		unRegisterEntity(e, world->currentLevel.battleCamp.gridSP);

		Entity parent = world->mPoolFollowingComponent.mPackedArray[i].parent;

		getCmpEntity(world->mPoolTransformBattleComponent, e).pos = getCmpEntity(world->mPoolTransformBattleComponent, parent).pos + world->mPoolFollowingComponent.mPackedArray[i].tranformPos;

		registerEntity(e, world->currentLevel.battleCamp.gridSP);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class BattleMoveSystem
//-----------------------------------------------------------------------------------------------------------------------------------------