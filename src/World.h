#pragma once

#include <vector>

#include "Data/Phase/PhaseHandler.h"

#include "Enviroment/TileSet.h"

//Including ComponentPools
#include "ECS/ComponentPool.h"

#include "Components/TransformComponent.h"
#include "Components/DrawComponent.h"
#include "Components/MoveComponent.h"
#include "Components/ActionComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/BaseEnemyComponent.h"
//Including ComponentPools

//Including some Data
#include "Data/Level/Level.h"
#include "Data/Camera/Camera.h"
//Including some Data

#include "Time/Delay.h"





using Player = Entity;



struct World
{
	//Phase handler
	PhaseHandler phaseHandler;
	//Phase handler

	//POOL OF COMPONENTS
	ComponentPool<TransformComponent> mPoolTransformComponent;
	ComponentPool<DrawComponent> mPoolDrawComponent;
	ComponentPool<MoveComponent> mPoolMoveComponent;
	ComponentPool<ActionComponent> mPoolActionComponent;
	ComponentPool<AnimationComponent> mPoolAnimationComponent;
	ComponentPool<BaseEnemyComponent> mPoolBaseEnemyComponent;
	//POOL OF COMPONENTS

	std::vector<Entity> battleEntities;
	std::vector<Entity> allertingEntities;
	Timer delayTransictionToBattle;

	//Camera
	Camera camera;
	CameraData cameraData;

	//Player
	Player player;

	//Levels of game
	Level currentLevel;
	//Base info

	///FOR TESTING
	//TILESET
	TileSetHandler mTileSetHandler;

	SDL_Texture* textureActor;
	TileSet* tilesetActor;
	
	Timer debugInfoTimer;
	///FOR TESTING
};