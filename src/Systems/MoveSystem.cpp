#include "Systems/MoveSystem.h"

//Including some general
#include "Direction.h"
//Including some general

//Include World
#include "Game.h"
#include "World.h"
//Include World

//Include some base ECS
#include "ECS/Entity.h"
#include "ECS/ComponentPool.h"
//Include some base ECS

//Including Components
#include "Components/MoveComponent.h"
#include "Components/TransformComponent.h"
//Including Components

//Including other Systems
#include "Systems/TileSystem.h"
//Including other Systems





void MoveSystem::move()
{
	Game* gameInstance = Game::get();
	World* world = Game::get()->getWorld();

	ComponentPool<TransformComponent>* TransformCmp = &world->mPoolTransformComponent;
	ComponentPool<MoveComponent>* MoveCmp = &world->mPoolMoveComponent;
	ComponentPool<ActionComponent>* ActionCmp = &world->mPoolActionComponent;

	float deltaTime = Game::get()->getDeltaTime();

	for (unsigned int i = 0; i < MoveCmp->mNext; i++)
	{
		Entity e = MoveCmp->mDirectArray[i];

		float incr;

		switch (ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction)
		{
		case WalkUp:
			incr = 1.0f / (ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].actionDelays[WalkUp].coolDown);
			TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos.y -= incr * deltaTime;
			break;
		case WalkDown:
			incr = 1.0f / (ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].actionDelays[WalkDown].coolDown);
			TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos.y += incr * deltaTime;
			break;
		case WalkRight:
			incr = 1.0f / (ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].actionDelays[WalkRight].coolDown);
			TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos.x += incr * deltaTime;
			break;
		case WalkLeft:
			incr = 1.0f / (ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].actionDelays[WalkLeft].coolDown);
			TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos.x -= incr * deltaTime;
			break;

		default:
			break;
		}
	}
}



void MoveSystem::endMove(Entity e)
{
	Game* gameInstance = Game::get();
	World* world = Game::get()->getWorld();

	ComponentPool<MoveComponent>* MoveCmp = &world->mPoolMoveComponent;
	ComponentPool<TransformComponent>* TransformCmp = &world->mPoolTransformComponent;

	//Fix position
	TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos = TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].tileOccupied;
	//Fix position

	//Set lastDirection to currentDirection
	MoveCmp->mPackedArray[MoveCmp->mReverseArray[e]].lastDirection = MoveCmp->mPackedArray[MoveCmp->mReverseArray[e]].currentDirection;
	//Set lastDirection to currentDirection

	//Reset currentDirection
	MoveCmp->mPackedArray[MoveCmp->mReverseArray[e]].currentDirection = NoneDirection;
	//Reset currentDirection
}



void MoveSystem::startMove(Entity e)
{
	Game* gameInstance = Game::get();
	World* world = Game::get()->getWorld();

	ComponentPool<TransformComponent>* TransformCmp = &world->mPoolTransformComponent;
	ComponentPool<MoveComponent>* MoveCmp = &world->mPoolMoveComponent;
	ComponentPool<ActionComponent>* ActionCmp = &world->mPoolActionComponent;

	Vector2i pos = TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos;
	Direction direction;

	switch (ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction)
	{
	case WalkUp:
		direction = Up;
		pos.y -= 1;
		break;
	case WalkDown:
		pos.y += 1;
		direction = Down;
		break;
	case WalkRight:
		pos.x += 1;
		direction = Right;
		break;
	case WalkLeft:
		pos.x -= 1;
		direction = Left;
		break;
	
	default:
		break;
	}



	//If the currentDirection is equal to the lastdirection do move
	if (MoveCmp->mPackedArray[MoveCmp->mReverseArray[e]].lastDirection != direction)
	{
		MoveCmp->mPackedArray[MoveCmp->mReverseArray[e]].currentDirection = direction;

		switch (direction)
		{
		case Up:
			ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction = RotateUp;
			break;
		case Down:
			ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction = RotateDown;
			break;
		case Right:
			ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction = RotateRight;
			break;
		case Left:
			ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction = RotateLeft;
			break;
		default:
			break;
		}

		start(&ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].actionDelays[ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction]);
	}
	//If the currentDirection is equal to the lastdirection do move
	//If the currentDirection is not equal to the lastdirection do rotation
	else
	{
		MoveCmp->mPackedArray[MoveCmp->mReverseArray[e]].currentDirection = direction;

		if (MoveSystem::isValid(pos, TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].z))
		{
			///Manca la registerPos della TileMap
			TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].tileOccupied = pos;
			start(&ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].actionDelays[ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction]);
		}
		else
		{
			ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction = NoneActions;
		}
	}
	//If the currentDirection is not equal to the lastdirection do rotation
}



bool MoveSystem::isValid(const Vector2f& pos, short int z)
{
	World* world = Game::get()->getWorld();

	if (pos.x < 0.0f 
		|| pos.x >= world->currentLevel.dim.x-1
		|| pos.y < 0.0f
		|| pos.y >= world->currentLevel.dim.y-1)
		return false;

	if (!TileSystem::isWalkable(pos, z))
		return false;

	return true;
}