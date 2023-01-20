#include "Scenes/BattleScene.h"

#include "ECS/ECS.h"

#include "utils/Physic/GridSP.h"

//Including Scenes
#include "Scenes/ExploringScene.h"
#include "Scenes/GeneralMenuScene.h"
//Including Scenes

//Including some Enviroment
#include "Enviroment/Input/Input.h"

#include "Enviroment/WindowHandler.h"
//Including some Enviroment

//Including some Systems
#include "Systems/Battle/ColliderSystem.h"
#include "Systems/Battle/BattleRenderSystem.h"
#include "Systems/Battle/BattleMoveSystem.h"
#include "Systems/Battle/BattleLifeSystem.h"
#include "Systems/Battle/ProjectileSystem.h"

#include "Systems/Battle/HitBoxSystem.h"

#include "Systems/Exploring/CameraSystem.h"
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



void BattleScene::loadScene()
{

}



void BattleScene::updateScene()
{
	if (status == statusScene::RunningScene)
	{
		World* world = getGame()->getWorld();

		//Clear buffers of collisions
		ColliderSystem::collisionsInfoClear();
		//Clear buffers of collisions

		//Update Move System
		BattleMoveSystem::controlledMoves();
		BattleMoveSystem::freeMove();
		BattleMoveSystem::followingMoves();
		//Update Move System

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

		//Check if is dead the hitBoxes
		HitBoxSystem::checkIfIsDead();
		//Check if is dead the hitBoxes

		//Update Camera
		CameraSystem::updateCamera(getCmpEntity<TransformBattleComponent>(world->BattlePlayerEntity).pos);
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
}



void BattleScene::generateOutputScene()
{
	//Here code to draw battle graphic element
	BattleRenderSystem::draw();

	BattleRenderSystem::drawColliders();
}



void BattleScene::processInputScene()
{
	if (status == statusScene::RunningScene)
	{
		//Handle principle events
		const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
		std::vector<Direction> directions;



		if (isPressedKey(SDL_SCANCODE_W))
			directions.push_back(Direction::Up);
		else if (isPressedKey(SDL_SCANCODE_S))
		{
			directions.push_back(Direction::Down);
		}
		else if (isPressedKey(SDL_SCANCODE_A))
		{
			directions.push_back(Direction::Left);
		}
		else if (isPressedKey(SDL_SCANCODE_D))
		{
			directions.push_back(Direction::Right);
		}

		if (isPressedKey(SDL_SCANCODE_M))
		{
			if (!isActiveScene<GeneralMenuScene>())
			{
				Game::get()->startGeneralMenu();
				Game::get()->getGeneraMenuScene()->choice = 1;
			}
		}

		if (isQuitted())
		{
			Game::get()->setRunning(false);
		}
		if (isResizedWindow())
		{
			SDL_Log("Window size changed to %dx%d", getWindowSize().x, getWindowSize().y);
			WindowHandler::get().updateWindowDimension(getWindowSize());
			CameraSystem::onUpdateWindowSize();
		}



		if (!directions.empty())
			getCmpEntity(world->mPoolPhysicBoxComponent, world->BattlePlayerEntity).lastDirection = directions.back();

		//Handle principle events



		if (keyStates[SDL_SCANCODE_W])
		{
			BattleMoveSystem::applyForce(world->BattlePlayerEntity, { 0.0f, -50.0f });
		}
		if (keyStates[SDL_SCANCODE_S])
		{
			BattleMoveSystem::applyForce(world->BattlePlayerEntity, { 0.0f, 50.0f });
		}
		if (keyStates[SDL_SCANCODE_D])
		{
			BattleMoveSystem::applyForce(world->BattlePlayerEntity, { 50.0f, 0.0f });
		}
		if (keyStates[SDL_SCANCODE_A])
		{
			BattleMoveSystem::applyForce(world->BattlePlayerEntity, { -50.0f, 0.0f });
		}
		if (keyStates[SDL_SCANCODE_M] && isEnd(world->delayFiring))
		{
			Entity projectile = EntityManager::get().createEntity();

			registerEntity(world->mPoolTransformBattleComponent, projectile);
			getCmpEntity(world->mPoolTransformBattleComponent, projectile).pos = getCmpEntity(world->mPoolTransformBattleComponent, world->BattlePlayerEntity).pos;

			registerEntity(world->mPoolPhysicBoxComponent, projectile);
			getCmpEntity(world->mPoolPhysicBoxComponent, projectile).lastDirection = getCmpEntity(world->mPoolPhysicBoxComponent, world->BattlePlayerEntity).lastDirection;
			getCmpEntity(world->mPoolPhysicBoxComponent, projectile).mass = 1.0f;
			getCmpEntity(world->mPoolPhysicBoxComponent, projectile).v = { 0.0f, 0.0f };

			registerEntity(world->mPoolRectColliderComponent, projectile);
			getCmpEntity(world->mPoolRectColliderComponent, projectile).dim = { 32, 32 };

			registerEntity(world->mPoolDrawBattleComponent, projectile);
			getCmpEntity(world->mPoolDrawBattleComponent, projectile).id = 117;
			getCmpEntity(world->mPoolDrawBattleComponent, projectile).tileSet = world->mTileSetHandler.getTileSet("data/player.png");
			getCmpEntity(world->mPoolDrawBattleComponent, projectile).dim = getCmpEntity(world->mPoolDrawBattleComponent, projectile).tileSet->tileDim;

			//Assign the categories
			registerEntity(world->mPoolFreeRectColliderComponent, projectile);

			registerEntity(world->mPoolPlayerBattleComponent, projectile);

			registerEntity(world->mPoolProjectileComponent, projectile);
			getCmpEntity(world->mPoolProjectileComponent, projectile).damage = 100.0f;
			//Assign the categories

			//Apply force to move the projectile
			switch (getCmpEntity(world->mPoolPhysicBoxComponent, projectile).lastDirection)
			{

			case Up:
				BattleMoveSystem::applyForce(projectile, { 0.0f, -100.0f });
				getCmpEntity(world->mPoolTransformBattleComponent, projectile).pos.y += -32.0f;
				break;

			case Down:
				BattleMoveSystem::applyForce(projectile, { 0.0f, 100.0f });
				getCmpEntity(world->mPoolTransformBattleComponent, projectile).pos.y += 32.0f;
				break;

			case Right:
				BattleMoveSystem::applyForce(projectile, { 100.0f, 0.0f });
				getCmpEntity(world->mPoolTransformBattleComponent, projectile).pos.x += 32.0f;
				break;

			case Left:
				BattleMoveSystem::applyForce(projectile, { -100.0f, 0.0f });
				getCmpEntity(world->mPoolTransformBattleComponent, projectile).pos.x += -32.0f;
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

			registerEntity(world->mPoolHitBoxComponent, entity);
			getCmpEntity(world->mPoolHitBoxComponent, entity).damage = 100.0f;
			getCmpEntity(world->mPoolHitBoxComponent, entity).delayHitBox.coolDown = 0.05f;
			getCmpEntity(world->mPoolHitBoxComponent, entity).delayHitBox.timePassed = 0.0f;

			registerEntity(world->mPoolFollowingComponent, entity);
			getCmpEntity(world->mPoolFollowingComponent, entity).parent = world->BattlePlayerEntity;

			registerEntity(world->mPoolRectColliderComponent, entity);

			registerEntity(world->mPoolDrawBattleComponent, entity);
			getCmpEntity(world->mPoolDrawBattleComponent, entity).tileSet = world->mTileSetHandler.getTileSet("data/brimstone.png");

			Direction direction = getCmpEntity(world->mPoolPhysicBoxComponent, world->BattlePlayerEntity).lastDirection;
			getCmpEntity(world->mPoolHitBoxComponent, entity).direction = direction;
			switch (direction)
			{
			case Up:
				getCmpEntity(world->mPoolFollowingComponent, entity).tranformPos = Vector2i(3, -120);
				getCmpEntity(world->mPoolRectColliderComponent, entity).dim = Vector2i(8, 120);
				getCmpEntity(world->mPoolDrawBattleComponent, entity).id = 0;
				getCmpEntity(world->mPoolDrawBattleComponent, entity).dim = Vector2i(8, 120);
				break;

			case Down:
				getCmpEntity(world->mPoolFollowingComponent, entity).tranformPos = Vector2i(3, 16);
				getCmpEntity(world->mPoolRectColliderComponent, entity).dim = Vector2i(8, 120);
				getCmpEntity(world->mPoolDrawBattleComponent, entity).id = 1;
				getCmpEntity(world->mPoolDrawBattleComponent, entity).dim = Vector2i(8, 120);
				break;

			case Right:
				getCmpEntity(world->mPoolFollowingComponent, entity).tranformPos = Vector2i(16, 3);
				getCmpEntity(world->mPoolRectColliderComponent, entity).dim = Vector2i(120, 8);
				getCmpEntity(world->mPoolDrawBattleComponent, entity).id = 2;
				getCmpEntity(world->mPoolDrawBattleComponent, entity).dim = Vector2i(120, 8);
				break;

			case Left:
				getCmpEntity(world->mPoolFollowingComponent, entity).tranformPos = Vector2i(-120, 3);
				getCmpEntity(world->mPoolRectColliderComponent, entity).dim = Vector2i(120, 8);
				getCmpEntity(world->mPoolDrawBattleComponent, entity).id = 3;
				getCmpEntity(world->mPoolDrawBattleComponent, entity).dim = Vector2i(120, 8);
				break;

			default:
				break;
			}

			registerEntity(world->mPoolTransformBattleComponent, entity);
			getCmpEntity(world->mPoolTransformBattleComponent, entity).pos = getCmpEntity(world->mPoolFollowingComponent, entity).tranformPos
				+ getCmpEntity(world->mPoolTransformBattleComponent, world->BattlePlayerEntity).pos;

			registerEntity(entity, world->currentLevel.battleCamp.gridSP);

			registerEntity(world->mPoolPlayerBattleComponent, entity);

			start(&world->delayHitBox);
		}
		if (keyStates[SDL_SCANCODE_P])
		{
			SDL_Log("Count Projectile: %d", world->mPoolProjectileComponent.mNext);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class BattleScene
//-----------------------------------------------------------------------------------------------------------------------------------------