#include "PrecompiledHeaders.h"

#include "Systems/Battle/BattleMoveSystem.h"
#include "Systems/Battle/ColliderSystem.h"

#include "utils/Math/Math.h"

//Including some context
#include "World.h"
#include "Game.h"
//Including some context

#define TEMP 100.0f





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

	//Clamp to the max value the velocity
	//if (std::abs(world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x) >= TEMP)
	//	world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x = TEMP;
	//if (std::abs(world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y) >= TEMP)
	//	world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y = TEMP;
	//Clamp to the max value the velocity
}



void BattleMoveSystem::applyFriction(Entity e, float friction = 1.0f)
{
	World* world = Game::get()->getWorld();

	world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x = 0.0f;
	world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y = 0.0f;
	////Controll if the entity is already stopped
	//if (world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x != 0.0f
	//	||
	//	world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y != 0.0f)
	//{
	//	float deltaTime = Game::get()->getDeltaTime();

	//	Vector2i signs;
	//	//Save the sign of the velocity of the entity
	//	if (world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x)
	//		signs.x = world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x / std::abs(world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x);
	//	if (world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y)
	//		signs.y = world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y / std::abs(world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y);
	//	//Save the sign of the velocity of the entity



	//	//Subtract to velocity the friction
	//	float fp = world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].mass * 9.81f;
	//	world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x += -1.0f * signs.x * friction * fp * deltaTime;
	//	world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y += -1.0f * signs.y * friction * fp * deltaTime;
	//	//Subtract to velocity the friction



	//	Vector2i signsAfter;
	//	//Save the sign of the velocity of the entity after we applied the friction
	//	if (world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x)
	//		signsAfter.x = world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x / std::abs(world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x);
	//	if (world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y)
	//		signsAfter.y = world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y / std::abs(world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y);
	//	//Save the sign of the velocity of the entity after we applied the friction



	//	//Clamp value of the velocity
	//	if (signsAfter.x != signs.x)
	//		world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.x = 0.0f;
	//	if (signsAfter.y != signs.y)
	//		world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v.y = 0.0f;
	//	//Clamp value of the velocity
	//}
	////Controll if the entity is already stopped
}



void BattleMoveSystem::freeMove()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolFreeRectColliderComponent.mNext; i++)
	{
		Entity e = world->mPoolFreeRectColliderComponent.mDirectArray[i];

		world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos +=
			world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].v * Game::get()->getDeltaTime();
	}
}



void BattleMoveSystem::controlledMoves()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolControlledRectColliderComponent.mNext; i++)
	{
		Entity e = world->mPoolControlledRectColliderComponent.mDirectArray[i];

		world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos +=
			world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].v * Game::get()->getDeltaTime();

		for (unsigned int j = 0; j < world->mPoolControlledRectColliderComponent.mNext; j++)
		{
			if (i != j)
			{
				Entity e2 = world->mPoolControlledRectColliderComponent.mDirectArray[j];

				if (ColliderSystem::detectCollision(world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos,
					world->mPoolRectColliderComponent.mPackedArray[world->mPoolRectColliderComponent.mReverseArray[e]].dim,
					world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e2]].pos,
					world->mPoolRectColliderComponent.mPackedArray[world->mPoolRectColliderComponent.mReverseArray[e2]].dim))
				{
					Vector2f penetration = ColliderSystem::penetration(world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos,
						world->mPoolRectColliderComponent.mPackedArray[world->mPoolRectColliderComponent.mReverseArray[e]].dim,
						world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e2]].pos,
						world->mPoolRectColliderComponent.mPackedArray[world->mPoolRectColliderComponent.mReverseArray[e2]].dim);

					Vector2i signs;
					if (world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos.x > world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e2]].pos.x)
						signs.x = -1;
					else
						signs.x = 1;

					if (world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos.y > world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e2]].pos.y)
						signs.y = -1;
					else
						signs.y = 1;

					if (penetration.x >= penetration.y)
					{
						world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos.x += signs.x * penetration.x;
					}
					else
					{
						world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos.y += signs.y * penetration.y;
					}

					world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].v = { 0.0f, 0.0f };
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class BattleMoveSystem
//-----------------------------------------------------------------------------------------------------------------------------------------