#pragma once

#include "Enviroment/TileSet.h"

//Including ComponentPools
#include "ECS/ComponentPool.h"

#include "Components/TransformComponent.h"
#include "Components/DrawComponent.h"
#include "Components/MoveComponent.h"
//Including ComponentPools

//Including some Data
#include "Data/Level/Level.h"
#include "Data/Camera/Camera.h"
//Including some Data

#include "Time/Delay.h"





using Player = Entity;



struct World
{
	//POOL OF COMPONENTS
	ComponentPool<TransformComponent> mPoolTransformComponent;
	ComponentPool<DrawComponent> mPoolDrawComponent;
	ComponentPool<MoveComponent> mPoolMoveComponent;
	//POOL OF COMPONENTS

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
	///FOR TESTING
};