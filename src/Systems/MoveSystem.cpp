#include "Systems/MoveSystem.h"

//Including some general
#include "Direction.h"
//Including some general

//Include World
#include "Game.h"
#include "World.h"
//Include World

//Including Components
#include "ECS/ComponentPool.h"
#include "Components/MoveComponent.h"
#include "Components/TransformComponent.h"
//Including Components





void MoveSystem::move()
{
	Game* gameInstance = Game::get();
	World* world = Game::get()->getWorld();

	ComponentPool<TransformComponent>* TransformCmp = &world->mPoolTransformComponent;
	ComponentPool<MoveComponent>* MoveCmp = &world->mPoolMoveComponent;

	for (unsigned int i = 0; i < MoveCmp->mNext; i++)
	{
		Entity e = MoveCmp->mDirectArray[i];

		Vector2f pos = TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos;

		switch (MoveCmp->mPackedArray[i].currentDirection)
		{
		case NoneDirection:
			break;
		
		case Up:
			pos.y -= 0.01f;
			break;
		case Down:
			pos.y += 0.01f;
			break;
		case Right:
			pos.x += 0.01f;
			break;
		case Left:
			pos.x -= 0.01f;
			break;

		default:
			break;
		}

		if (MoveSystem::isValid(pos))
		{
			TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos = pos;
		}

		MoveCmp->mPackedArray[i].currentDirection = NoneDirection;
	}

}



bool MoveSystem::isValid(const Vector2f& pos)
{
	World* world = Game::get()->getWorld();

	if (pos.x < 0.0f 
		|| pos.x >= world->currentLevel.dim.x-1
		|| pos.y < 0.0f
		|| pos.y >= world->currentLevel.dim.y-1)
		return false;

	return true;
}