#pragma once

#include <vector>

#include <set>
#include <iterator>

#include "Enviroment/TileSet.h"

//Including ComponentPools
#include "ECS/ComponentPool.h"

#include "Components/Exploring/TransformComponent.h"
#include "Components/Exploring/DrawComponent.h"
#include "Components/Exploring/MoveComponent.h"
#include "Components/Exploring/ActionComponent.h"
#include "Components/Exploring/AnimationComponent.h"
#include "Components/Exploring/BaseEnemyComponent.h"
#include "Components/Exploring/BagComponent.h"

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
#include "Components/Battle/ProjectileComponent.h"
#include "Components/Battle/DamageComponent.h"
#include "Components/Battle/HitBoxComponent.h"
#include "Components/Battle/FollowingComponent.h"
//Including ComponentPools

//Including some Data
#include "Data/Level/Level.h"
#include "Data/Camera/Camera.h"
//Including some Data





using Player = Entity;



struct World
{
	//POOL OF COMPONENTS
	ComponentPool<TransformComponent> mPoolTransformComponent;
	ComponentPool<DrawComponent> mPoolDrawComponent;
	ComponentPool<MoveComponent> mPoolMoveComponent;
	ComponentPool<ActionComponent> mPoolActionComponent;
	ComponentPool<AnimationComponent> mPoolAnimationComponent;
	ComponentPool<BaseEnemyComponent> mPoolBaseEnemyComponent;
	ComponentPool<BagComponent> mPoolBagComponent;

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
	ComponentPool<DamageComponent> mPoolDamageComponent;

	ComponentPool<ProjectileComponent> mPoolProjectileComponent;

	ComponentPool<FollowingComponent> mPoolFollowingComponent;
	ComponentPool<HitBoxComponent> mPoolHitBoxComponent;

	ComponentPool<StateBattleComponent> mPoolStateBattleComponent;
	//POOL OF BATTLE-COMPONENTS

	//POOL OF COMPONENTS

	//For the Exploring Phase
	std::vector<Entity> battleEntities;
	std::vector<Entity> allertingEntities;
	Timer delayTransictionToBattle;
	//For the Exploring Phase

	//For the Battle Phase
	std::vector<std::pair<Entity, Entity>> collisions;
	std::set<Entity> entitiesInCollisions;

	std::set<Entity> entityToDelete;
	//std::vector<Entity> entityToAdd;

	//For the Battle Phase

	//Camera
	Camera camera;
	CameraData cameraData;
	CameraData backupBattleCameraData;
	CameraData backupExploringCameraData;

	//Player
	Player player;
	Entity BattlePlayerEntity;
	Timer delayFiring;
	Timer delayHitBox;

	//Levels of game
	Level currentLevel;

	///FOR TESTING
	//TILESET
	TileSetHandler mTileSetHandler;

	SDL_Texture* textureActor;
	TileSet* tilesetActor;
	
	Timer debugInfoTimer;
	///FOR TESTING
};