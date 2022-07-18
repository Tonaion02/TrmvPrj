#include "Scenes/BattleScene.h"

#include "ECS/ECS.h"

#include "utils/Physic/GridSP.h"

//Including some Systems
#include "Systems/Battle/ColliderSystem.h"
#include "Systems/Battle/BattleRenderSystem.h"
#include "Systems/Battle/BattleMoveSystem.h"
#include "Systems/Battle/BattleLifeSystem.h"
#include "Systems/Battle/ProjectileSystem.h"

#include "Systems/CameraSystem.h"

#include "Systems/Battle/FollowingSystem.h"
//Including some Systems

//Including some Context
#include "Game.h"
#include "World.h"
//Including some Context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class BattleScene
//-----------------------------------------------------------------------------------------------------------------------------------------
BattleScene::BattleScene()
	:BaseScene(idTypeScenes<BattleScene>())
{

}



void BattleScene::updateScene()
{
	World* world = getGame()->getWorld();

	//Clear buffers of collisions
	ColliderSystem::collisionsInfoClear();
	//Clear buffers of collisions

	//Update Move System
	BattleMoveSystem::controlledMoves();
	BattleMoveSystem::freeMove();
	//Update Move System

	//Update Following System
	FollowingSystem::update();
	//Update Following System

	//Apply friction
	BattleMoveSystem::applyFriction(world->BattlePlayerEntity, 8.0f);
	//Apply friction

	//Trying to detect Collisions
	ColliderSystem::detectCollisions();
	//Trying to detect Collisions

	//Detect collisions and apply damage
	LifeSystem::applyDamage();
	//Detect collisions and apply damage

	//Check if the projectile is dead
	ProjectileSystem::checkIfIsDeadProjectile();
	//Check if the projectile is dead

	//Update Camera
	CameraSystem::updateCamera(getCmpEntity<TransformBattleComponent>(world->BattlePlayerEntity)->pos);
	//Update Camera

	//Update timer
	world->delayFiring.timePassed += getGame()->getDeltaTime();
	world->delayHitBox.timePassed += getGame()->getDeltaTime();
	//Update timer

	//Check if some Entities is died
	LifeSystem::checkIfIsDead();
	//Check if some Entities is died



	LifeSystem::cleanDeadEntity();
	LifeSystem::cleanInfo();
}



void BattleScene::generateOutputScene()
{
	//Here code to draw battle graphic element
	BattleRenderSystem::draw();

	BattleRenderSystem::drawColliders();
}



void BattleScene::processInputScene()
{
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);



	if (keyStates[SDL_SCANCODE_W])
	{
		BattleMoveSystem::applyForce(world->BattlePlayerEntity, { 0.0f, -50.0f });
		world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[world->BattlePlayerEntity]].lastDirection = Direction::Up;
	}
	if (keyStates[SDL_SCANCODE_S])
	{
		BattleMoveSystem::applyForce(world->BattlePlayerEntity, { 0.0f, 50.0f });
		world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[world->BattlePlayerEntity]].lastDirection = Direction::Down;
	}
	if (keyStates[SDL_SCANCODE_D])
	{
		BattleMoveSystem::applyForce(world->BattlePlayerEntity, { 50.0f, 0.0f });
		world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[world->BattlePlayerEntity]].lastDirection = Direction::Right;
	}
	if (keyStates[SDL_SCANCODE_A])
	{
		BattleMoveSystem::applyForce(world->BattlePlayerEntity, { -50.0f, 0.0f });
		world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[world->BattlePlayerEntity]].lastDirection = Direction::Left;
	}
	if (keyStates[SDL_SCANCODE_M] && isEnd(world->delayFiring))
	{
		Entity projectile = EntityManager::get().createEntity();

		registerEntity(&world->mPoolTransformBattleComponent, projectile);
		getCmpEntity(&world->mPoolTransformBattleComponent, projectile)->pos = getCmpEntity(&world->mPoolTransformBattleComponent, world->BattlePlayerEntity)->pos;

		registerEntity(&world->mPoolPhysicBoxComponent, projectile);
		getCmpEntity(&world->mPoolPhysicBoxComponent, projectile)->lastDirection = getCmpEntity(&world->mPoolPhysicBoxComponent, world->BattlePlayerEntity)->lastDirection;
		getCmpEntity(&world->mPoolPhysicBoxComponent, projectile)->mass = 1.0f;
		getCmpEntity(&world->mPoolPhysicBoxComponent, projectile)->v = { 0.0f, 0.0f };

		registerEntity(&world->mPoolRectColliderComponent, projectile);
		getCmpEntity(&world->mPoolRectColliderComponent, projectile)->dim = { 16, 16 };

		registerEntity(&world->mPoolDrawBattleComponent, projectile);
		getCmpEntity(&world->mPoolDrawBattleComponent, projectile)->id = 117;
		getCmpEntity(&world->mPoolDrawBattleComponent, projectile)->personalScale = 1.0f;

		//Assign the categories
		registerEntity(&world->mPoolFreeRectColliderComponent, projectile);
		registerEntity(&world->mPoolPlayerBattleComponent, projectile);

		registerEntity(&world->mPoolProjectileComponent, projectile);
		getCmpEntity(&world->mPoolProjectileComponent, projectile)->damage = 100.0f;
		//Assign the categories

		//Apply force to move the projectile
		switch (getCmpEntity(&world->mPoolPhysicBoxComponent, projectile)->lastDirection)
		{

		case Up:
			BattleMoveSystem::applyForce(projectile, { 0.0f, -100.0f });
			break;

		case Down:
			BattleMoveSystem::applyForce(projectile, { 0.0f, 100.0f });
			break;

		case Right:
			BattleMoveSystem::applyForce(projectile, { 100.0f, 0.0f });
			break;

		case Left:
			BattleMoveSystem::applyForce(projectile, { -100.0f, 0.0f });
			break;

		default:
			break;
		}
		//Apply force to move the projectile

		//Start the timer of delayFiring
		start(&world->delayFiring);
		//Start the timer of delayFiring
	}
	if (keyStates[SDL_SCANCODE_N] && isEnd(world->delayHitBox))
	{
		Entity entity = createEntityId();

		registerEntity(&world->mPoolHitBoxComponent, entity);
		getCmpEntity(&world->mPoolHitBoxComponent, entity)->damage = 100.0f;

		registerEntity(&world->mPoolFollowingComponent, entity);
		getCmpEntity(&world->mPoolFollowingComponent, entity)->parent = world->BattlePlayerEntity;
		getCmpEntity(&world->mPoolFollowingComponent, entity)->tranformPos = Vector2i(0, 16);

		registerEntity(&world->mPoolTransformBattleComponent, entity);
		getCmpEntity(&world->mPoolTransformBattleComponent, entity)->pos = getCmpEntity(&world->mPoolFollowingComponent, entity)->tranformPos 
																		 + getCmpEntity(&world->mPoolTransformBattleComponent, world->BattlePlayerEntity)->pos;

		registerEntity(&world->mPoolRectColliderComponent, entity);
		getCmpEntity(&world->mPoolRectColliderComponent, entity)->dim = Vector2i(32, 120);

		unRegisterEntity(entity, world->currentLevel.battleCamp.gridSP);
		registerEntity(entity, world->currentLevel.battleCamp.gridSP);

		registerEntity(&world->mPoolPlayerBattleComponent, entity);

		//registerEntity(&world->mPoolDrawBattleComponent, entity);
	}
	if (keyStates[SDL_SCANCODE_P])
	{
		SDL_Log("Count Projectile: %d", world->mPoolProjectileComponent.mNext);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class BattleScene
//-----------------------------------------------------------------------------------------------------------------------------------------