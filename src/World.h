#pragma once

#include <vector>

#include <set>
#include <iterator>

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

#include "Components/Battle/TransformBattleComponent.h"
#include "Components/Battle/DrawBattleComponent.h"
#include "Components/Battle/AnimationBattleComponent.h"
#include "Components/Battle/RectColliderComponent.h"
#include "Components/Battle/MoveBattleComponent.h"
#include "Components/Battle/PyshicBoxComponent.h"
#include "Components/Battle/EnemyBattleComponent.h"
#include "Components/Battle/PlayerBattleComponent.h"
#include "Components/Battle/ControlledRectCollider.h"
#include "Components/Battle/FreeRectCollider.h"
#include "Components/Battle/LifeBarComponent.h"
#include "Components/Battle/StateBattleComponent.h"
//Including ComponentPools

//Including some Data
#include "Data/Level/Level.h"
#include "Data/Camera/Camera.h"
//Including some Data





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

	//POOL OF BATTLE-COMPONENTS
	ComponentPool<TransformBattleComponent> mPoolTransformBattleComponent;
	ComponentPool<AnimationBattleComponent> mPoolAnimationBattleComponent;
	ComponentPool<DrawBattleComponent> mPoolDrawBattleComponent;
	ComponentPool<RectColliderComponent> mPoolRectColliderComponent;
	ComponentPool<MoveBattleComponent> mPoolMoveBattleComponent;
	ComponentPool<PyshicBoxComponent> mPoolPhysicBoxComponent;
	ComponentPool<EnemyBattleComponent> mPoolEnemyBattleComponent;
	ComponentPool<PlayerBattleComponent> mPoolPlayerBattleComponent;
	ComponentPool<ControlledRectCollider> mPoolControlledRectColliderComponent;
	ComponentPool<FreeRectCollider> mPoolFreeRectColliderComponent;
	ComponentPool<LifeBarComponent> mPoolLifeBarComponent;

	ComponentPool<StateBattleComponent> mPoolStateBattleComponent;
	//POOL OF BATTLE-COMPONENTS

	std::vector<std::pair<Entity, Entity>> collisions;
	//std::vector<Entity> entitiesInCollisions;
	std::set<Entity> entitiesInCollisions;
	//POOL OF COMPONENTS

	//For the Exploring Phase
	std::vector<Entity> battleEntities;
	std::vector<Entity> allertingEntities;
	Timer delayTransictionToBattle;
	//For the Exploring Phase

	//Camera
	Camera camera;
	CameraData cameraData;
	CameraData backupBattleCameraData;
	CameraData backupExploringCameraData;

	//Player
	Player player;
	Entity BattlePlayerEntity;
	Timer delayFiring;

	//Levels of game
	Level currentLevel;
	
	//Base info

	///FOR TESTING
	//TILESET
	TileSetHandler mTileSetHandler;

	SDL_Texture* textureActor;
	TileSet* tilesetActor;
	
	Timer debugInfoTimer;

	Entity entityToMove;
	///FOR TESTING
};