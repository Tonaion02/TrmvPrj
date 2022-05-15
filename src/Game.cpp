#include "Game.h"

#include "ECS/TypeManager.h"

//Including Some Utils
#include "Misc/Direction.h"
#include "Misc/Grid.h"
//Including Some Utils

//Including PhaseHandler
#include "Data/Phase/Phase.h"
#include "Data/Phase/PhaseHandler.h"
//Including PhaseHandler

//Including Enviroment
#include "Enviroment/WindowHandler.h"
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including Ecs
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/System.h"
//Including Ecs

//Including System
#include "Systems/RenderSystem.h"
#include "Systems/MoveSystem.h"
#include "Systems/CameraSystem.h"
#include "Systems/ActionSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/TileSystem.h"
#include "Systems/EnemySystem.h"

//Including Battle System
#include "Systems/Battle/BattleRenderSystem.h"
#include "Systems/Battle/BattleMoveSystem.h"
#include "Systems/Battle/ColliderSystem.h"
#include "Systems/Battle/BattleLifeSystem.h"
//Including Battle System
//Including System

//Some Shit
#include "World.h"
//Some Shit





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Game
//-----------------------------------------------------------------------------------------------------------------------------------------
const float Game::sMaxDeltaTime = 0.5f;
Game* Game::sGameInstance = nullptr;





void Game::update()
{
	for (auto iter : world->phaseHandler.phaseStack)
	{
		if (iter->phaseType == PhaseType::Exploring)
		{
			if (iter->statePhase == StatePhase::On)
			{
				//First input and then AI decides what is the action

				//Execute current action of all Entity
				MoveSystem::move();

				AnimationSystem::animate();

				CameraSystem::updateCamera(world->mPoolTransformComponent.mPackedArray[
					world->mPoolTransformComponent.mReverseArray[world->player]].pos);
				//Execute current action of all Entity

				//Update Component
				ActionSystem::updateAction();
				//Update Component

				//Update debugInfoTimer
				if (!isEnd(world->debugInfoTimer))
				{
					world->debugInfoTimer.timePassed += mDeltaTime;
				}
				//Update debugInfoTimer

				//Controll if the action is ended
				ActionSystem::endAction();
				//Controll if the action is ended

				//Now the action that is ended is set to NoneAction
				EnemySystem::aiBaseEnemy();
			}
		}
		else if (iter->phaseType == PhaseType::Battle)
		{
			//Clear buffers of collisions
			ColliderSystem::collisionsInfoClear();
			//Clear buffers of collisions

			//Update Move System
			BattleMoveSystem::controlledMoves();
			BattleMoveSystem::freeMove();
			//Update Move System

			//Apply friction
			BattleMoveSystem::applyFriction(world->BattlePlayerEntity, 8.0f);
			//Apply friction

			//Trying to detect Collisions
			ColliderSystem::detectCollisions();
			//Trying to detect Collisions

			//Detect collisions and apply damage
			LifeSystem::onCollision();
			//Detect collisions and apply damage

			//Update Camera
			CameraSystem::updateCamera(world->mPoolTransformBattleComponent.mPackedArray[
				world->mPoolTransformBattleComponent.mReverseArray[world->player]].pos);
			//Update Camera

			//Update timer
			world->delayFiring.timePassed += mDeltaTime;
			//Update timer
		}
	}
}



void Game::processInput()
{
	//General handling of the Input
	SDL_Event event;

	//Handle principle events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				SDL_Log("Window %d size changed to %dx%d", event.window.windowID, event.window.data1, event.window.data2);
				WindowHandler::get().updateWindowDimension({ event.window.data1, event.window.data2 });
				CameraSystem::onUpdateWindowSize();
				break;
			}
			break;
		}
	}
	//Handle principle events
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	//General commands
	
	//For zooming camera in and out
	if (keyStates[SDL_SCANCODE_1])
	{
		CameraSystem::updateCameraZoom(1.0f);
	}
	if (keyStates[SDL_SCANCODE_2])
	{
		CameraSystem::updateCameraZoom(-1.0f);
	}
	//For zooming camera in and out
	
	//General commands

	//General handling of the Input



	//Handling of the Input from the various phase
	for (auto iter : world->phaseHandler.phaseStack)
	{
		if (iter->phaseType == PhaseType::Exploring && iter->statePhase == StatePhase::On)
		{
			//For debugging
			if (keyStates[SDL_SCANCODE_B])
			{
				SignatureManager::get();
			}
			//For debugging



			//For moving player
			if (keyStates[SDL_SCANCODE_W])
			{
				if (ActionSystem::isDoingNothing(world->player) && world->battleEntities.empty() )
				{
					ActionSystem::startAction(world->player, Actions::Walk);
					MoveSystem::startMove(world->player, Direction::Up);
					AnimationSystem::startAnimation(world->player);
				}
			}
			else if (keyStates[SDL_SCANCODE_S] && world->battleEntities.empty() )
			{
				if (ActionSystem::isDoingNothing(world->player))
				{
					ActionSystem::startAction(world->player, Actions::Walk);
					MoveSystem::startMove(world->player, Direction::Down);
					AnimationSystem::startAnimation(world->player);
				}
			}
			else if (keyStates[SDL_SCANCODE_D])
			{
				if (ActionSystem::isDoingNothing(world->player) && world->battleEntities.empty() )
				{
					ActionSystem::startAction(world->player, Actions::Walk);
					MoveSystem::startMove(world->player, Direction::Right);
					AnimationSystem::startAnimation(world->player);
				}
			}
			else if (keyStates[SDL_SCANCODE_A] && world->battleEntities.empty() )
			{
				if (ActionSystem::isDoingNothing(world->player))
				{
					ActionSystem::startAction(world->player, Actions::Walk);
					MoveSystem::startMove(world->player, Direction::Left);
					AnimationSystem::startAnimation(world->player);
				}
			}
			//For moving player



			//For debuggingInfo
			else if (keyStates[SDL_SCANCODE_3] && isEnd(world->debugInfoTimer))
			{
				SDL_Log(
					"Player pos: ( %f, %f )",
					world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos.x,
					world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos.y
				);

				start(&world->debugInfoTimer);
			}
			//For debuggingInfo



			//For startingBattle
			else if (keyStates[SDL_SCANCODE_4])
			{
				static bool first = true;

				Game::startBattle();

				first = false;
			}
			//For startingBattle
		}
		else if (iter->phaseType == PhaseType::Battle)
		{
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
				//world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[projectile]].pos = world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[world->BattlePlayerEntity]].pos;
				
				registerEntity(&world->mPoolPhysicBoxComponent, projectile);
				getCmpEntity(&world->mPoolPhysicBoxComponent, projectile)->lastDirection = getCmpEntity(&world->mPoolPhysicBoxComponent, world->BattlePlayerEntity)->lastDirection;
				getCmpEntity(&world->mPoolPhysicBoxComponent, projectile)->mass = 1.0f;
				getCmpEntity(&world->mPoolPhysicBoxComponent, projectile)->v = { 0.0f, 0.0f };
				//world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[projectile]].lastDirection = world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[world->BattlePlayerEntity]].lastDirection;
				//world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[projectile]].mass = 1.0f;
				//world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[projectile]].v = { 0.0f, 0.0f };
				
				registerEntity(&world->mPoolRectColliderComponent, projectile);
				getCmpEntity(&world->mPoolRectColliderComponent, projectile)->dim = { 16, 16 };
				//world->mPoolRectColliderComponent.mPackedArray[world->mPoolRectColliderComponent.mReverseArray[projectile]].dim = { 16, 16 };
				
				registerEntity(&world->mPoolDrawBattleComponent, projectile);
				getCmpEntity(&world->mPoolDrawBattleComponent, projectile)->id = 117;
				getCmpEntity(&world->mPoolDrawBattleComponent, projectile)->personalScale = 1.0f;
				//world->mPoolDrawBattleComponent.mPackedArray[world->mPoolDrawBattleComponent.mReverseArray[projectile]].id = 117;
				//world->mPoolDrawBattleComponent.mPackedArray[world->mPoolDrawBattleComponent.mReverseArray[projectile]].personalScale = 1.0f;
				
				//Assign the categories
				registerEntity(&world->mPoolFreeRectColliderComponent, projectile);
				registerEntity(&world->mPoolPlayerBattleComponent, projectile);
				
				registerEntity(&world->mPoolProjectileComponent, projectile);
				getCmpEntity(&world->mPoolProjectileComponent, projectile)->damage = 100.0f;

				SDL_Log("Projectile: %d\n", (int)SignatureManager::get().isThereTypeCmp(projectile, getIndexFromType<ProjectileComponent>()));
				//Assign the categories

				//Apply force to move the projectile
				switch (getCmpEntity(&world->mPoolPhysicBoxComponent, projectile)->lastDirection)
				{

				case Up:
					BattleMoveSystem::applyForce(projectile, { 0.0f, -100.0f } );
					break;

				case Down:
					BattleMoveSystem::applyForce(projectile, { 0.0f, 100.0f } );
					break;

				case Right:
					BattleMoveSystem::applyForce(projectile, { 100.0f, 0.0f } );
					break;

				case Left:
					BattleMoveSystem::applyForce(projectile, { -100.0f, 0.0f } );
					break;

				default:
					break;
				}
				//Apply force to move the projectile

				//Start the timer of delayFiring
				start(&world->delayFiring);
				//Start the timer of delayFiring
			}
		}
	}
	//Handling of the Input from the various phase
}



void Game::generateOutput()
{
	//Clean screen
	SDL_SetRenderDrawColor(WindowHandler::get().getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(WindowHandler::get().getRenderer());
	//Clean screen



	for (auto iter : world->phaseHandler.phaseStack)
	{
		if (iter->phaseType == PhaseType::Exploring)
		{
			if (iter->statePhase != StatePhase::Paused)
			{
				//Prepare rendering
				RenderSystem::draw();
				//Prepare rendering
			}
		}
		else if (iter->phaseType == PhaseType::Battle)
		{
			//Here code to draw battle graphic element
			BattleRenderSystem::draw();

			BattleRenderSystem::drawColliders();
		}
	}



	//Render elements
	SDL_RenderPresent(WindowHandler::get().getRenderer());
	//Render elements
}



void Game::loadData()
{
	///Testing TypeManager
	SDL_Log("%u\n", getIndexFromType<DrawComponent>() );
	SDL_Log("%u\n", getIndexFromType<TransformComponent>() );
	SDL_Log("%u\n", getIndexFromType<DrawComponent>() );
	SDL_Log("%u\n", getIndexFromType<TransformComponent>() );
	SDL_Log("%u\n", getIndexFromType<FreeRectCollider>() );
	SDL_Log("%u\n", getIndexFromType<TransformComponent>());
	SDL_Log("Index : %u\n", getIndexFromType<PlayerBattleComponent>());
	///Testing TypeManager



	//Init some base data
	mIsRunning = true;

	mVsync = false;

	mDebugMode = true;

	mDeltaTime = 0.0f;
	mTicksCount = 0.0f;
	//Init some base data



	//Init world
	world = new World();
	//Init world



	//Load TileSet and Texture
	world->currentLevel.texture = TextureHandler::get().getTexture("data/buch-outdoor.png");
	world->mTileSetHandler.loadTileSet("data/buch-outdoor.png", 16);
	world->currentLevel.tileSet = *world->mTileSetHandler.getTileSet("data/buch-outdoor.png");
	world->textureActor = TextureHandler::get().getTexture("data/player.png");
	world->mTileSetHandler.loadTileSet("data/player.png", 16);
	world->tilesetActor = world->mTileSetHandler.getTileSet("data/player.png");
	//Load TileSet and Texture



	//Load Level	
	world->currentLevel = levelWrapper("casual generate level");
	//Load Level



	///FOR TESTING

	//Init debugTimer
	world->debugInfoTimer.coolDown = 1.0f;
	initTimer(&world->debugInfoTimer);
	//Init debugTimer

	float x = 0.0f;
	short int z = 0;

	for (int i = 0; i < 5; i++)
	{
		Entity e = EntityManager::get().createEntity();

		registerEntity(&world->mPoolTransformComponent, e);
		getCmpEntity(&world->mPoolTransformComponent, e)->pos = { x, x };
		getCmpEntity(&world->mPoolTransformComponent, e)->tileOccupied = { (int)x, (int)x };
		getCmpEntity(&world->mPoolTransformComponent, e)->z = z;
		//world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[e]].pos = { x, x };
		//world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[e]].tileOccupied = { (int)x, (int)x };
		//world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[e]].z = z;
		registerEntity(&world->mPoolDrawComponent, e);
		getCmpEntity(&world->mPoolDrawComponent, e)->id = 17;
		//world->mPoolDrawComponent.mPackedArray[world->mPoolDrawComponent.mReverseArray[e]].id = 17;

		if (e != 1)
		{
			TileSystem::registerPos({ (int)x,(int)x }, z, e);

			registerEntity(&world->mPoolMoveComponent, e);
			getCmpEntity(&world->mPoolMoveComponent, e)->currentDirection = NoneDirection;
			getCmpEntity(&world->mPoolMoveComponent, e)->lastDirection = Direction::Right;
			//world->mPoolMoveComponent.mPackedArray[world->mPoolMoveComponent.mReverseArray[e]].currentDirection = NoneDirection;
			//world->mPoolMoveComponent.mPackedArray[world->mPoolMoveComponent.mReverseArray[e]].lastDirection = Direction::Right;

			registerEntity(&world->mPoolActionComponent, e);
			getCmpEntity(&world->mPoolActionComponent, e)->currentAction = NoneActions;
			getCmpEntity(&world->mPoolActionComponent, e)->actionDelays[Actions::Walk].coolDown = 0.5f;
			getCmpEntity(&world->mPoolActionComponent, e)->actionDelays[Actions::Rotate].coolDown = 0.5f;
			//world->mPoolActionComponent.mPackedArray[world->mPoolActionComponent.mReverseArray[e]].currentAction = NoneActions;
			//world->mPoolActionComponent.mPackedArray[world->mPoolActionComponent.mReverseArray[e]].actionDelays[Actions::Walk].coolDown = 0.5f;
			//world->mPoolActionComponent.mPackedArray[world->mPoolActionComponent.mReverseArray[e]].actionDelays[Actions::Rotate].coolDown = 0.5f;

			registerEntity(&world->mPoolAnimationComponent, e);
			TiledAnimation tiledAnimation;
			tiledAnimation.ids = { 17 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::NoneActions, Direction::Up);
			tiledAnimation.ids = { 20 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::NoneActions, Direction::Down);
			tiledAnimation.ids = { 26 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::NoneActions, Direction::Right);
			tiledAnimation.ids = { 23 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::NoneActions, Direction::Left);

			tiledAnimation.ids = { 18, 19 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Walk, Direction::Up);
			tiledAnimation.ids = { 21, 22 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Walk, Direction::Down);
			tiledAnimation.ids = { 27, 28 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Walk, Direction::Right);
			tiledAnimation.ids = { 24, 25 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Walk, Direction::Left);

			tiledAnimation.ids = { 17 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Rotate, Direction::Up);
			tiledAnimation.ids = { 20 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Rotate, Direction::Down);
			tiledAnimation.ids = { 26 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Rotate, Direction::Right);
			tiledAnimation.ids = { 23 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Rotate, Direction::Left);
		}
		
		if (e == 2)
		{
			registerEntity(&world->mPoolBaseEnemyComponent, e);

			std::vector<Direction> path;
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Down);
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Down);
			path.push_back(Direction::Down);

			//world->mPoolBaseEnemyComponent.mPackedArray[world->mPoolBaseEnemyComponent.mReverseArray[e]].path = path;
			getCmpEntity(&world->mPoolBaseEnemyComponent, e)->path = path;
		}

		x += 1.0f;
	}



	world->player = 1;

	TileSystem::unRegisterPos(world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].tileOccupied, z);
	world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos = { 7.0f, 7.0f };
	world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].tileOccupied =
		static_cast<Vector2i>(world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos);
	TileSystem::registerPos(world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].tileOccupied, z, world->player);

	registerEntity(&world->mPoolMoveComponent, world->player);
	world->mPoolMoveComponent.mPackedArray[world->mPoolMoveComponent.mReverseArray[world->player]].currentDirection = NoneDirection;
	world->mPoolMoveComponent.mPackedArray[world->mPoolMoveComponent.mReverseArray[world->player]].lastDirection = Direction::Down;

	///Register and init entity to PoolActionComponent
	registerEntity(&world->mPoolActionComponent, world->player);

	world->mPoolActionComponent.mPackedArray[world->mPoolActionComponent.mReverseArray[world->player]].currentAction = NoneActions;

	world->mPoolActionComponent.mPackedArray[world->mPoolActionComponent.mReverseArray[world->player]].actionDelays[Actions::Walk].coolDown = 0.5f;
	world->mPoolActionComponent.mPackedArray[world->mPoolActionComponent.mReverseArray[world->player]].actionDelays[Actions::Rotate].coolDown = 0.2f;
	///Register and init entity to PoolActionComponent

	///Register and init entity to poolAnimationComponent
	registerEntity(&world->mPoolAnimationComponent, world->player);

 	TiledAnimation tiledAnimation;

	tiledAnimation.ids = { 17 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::NoneActions, Direction::Up);
	tiledAnimation.ids = { 20 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::NoneActions, Direction::Down);
	tiledAnimation.ids = { 26 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::NoneActions, Direction::Right);
	tiledAnimation.ids = { 23 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::NoneActions, Direction::Left);

	tiledAnimation.ids = { 18, 19 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Walk, Direction::Up);
	tiledAnimation.ids = { 21, 22 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Walk, Direction::Down);
	tiledAnimation.ids = { 27, 28 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Walk, Direction::Right);
	tiledAnimation.ids = { 24, 25 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Walk, Direction::Left);

	tiledAnimation.ids = { 17 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Rotate, Direction::Up);
	tiledAnimation.ids = { 20 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Rotate, Direction::Down);
	tiledAnimation.ids = { 26 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Rotate, Direction::Right);
	tiledAnimation.ids = { 23 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Rotate, Direction::Left);
	///Register and init entity to poolAnimationComponent



	///Init delayTransiction
	world->delayTransictionToBattle.coolDown = world->mPoolActionComponent.mPackedArray[world->mPoolActionComponent.mReverseArray[world->player]].actionDelays[Actions::Walk].coolDown
		+ 0.5f;
	///Init delayTransiction
	
	
	
	///Init camera
	Camera camera = EntityManager::get().createEntity();
	world->camera = camera;
	//registerEntity(&world->mPoolTransformComponent, camera);
	//world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[camera]].pos
	//	=
	//	world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos;

	///Init camera



	///Init test for Battle Phase
	int n = 2;
	for (int i = 0; i < n; i++)
	{
		Entity e = EntityManager::get().createEntity();

		registerEntity(&world->mPoolTransformBattleComponent, e);
		if (i == 0)
		{
			world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos = { 80.0f, 1.0f };
			world->BattlePlayerEntity = e;
			registerEntity(&world->mPoolPlayerBattleComponent, e);

			world->delayFiring.coolDown = 0.05f;
			initTimer(&world->delayFiring);
		}
		else
		{
			getCmpEntity(&world->mPoolTransformBattleComponent, e)->pos = { 60.0f, 1.0f };
			registerEntity(&world->mPoolEnemyBattleComponent, e);
		}
		registerEntity(&world->mPoolControlledRectColliderComponent, e);
		registerEntity(&world->mPoolPhysicBoxComponent, e);

		getCmpEntity(&world->mPoolPhysicBoxComponent, e)->mass = 1.0f;
		//world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].mass = 1.0f;
		getCmpEntity(&world->mPoolPhysicBoxComponent, e)->v = { 0.0f, 0.0f };
		//world->mPoolPhysicBoxComponent.mPackedArray[world->mPoolPhysicBoxComponent.mReverseArray[e]].v = { 0.0f, 0.0f };
		registerEntity(&world->mPoolRectColliderComponent, e);
		world->mPoolRectColliderComponent.mPackedArray[world->mPoolRectColliderComponent.mReverseArray[e]].dim = { 16, 16 };
		registerEntity(&world->mPoolDrawBattleComponent, e);
		world->mPoolDrawBattleComponent.mPackedArray[world->mPoolDrawBattleComponent.mReverseArray[e]].id = 17;

		registerEntity(&world->mPoolLifeBarComponent, e);
		getCmpEntity(&world->mPoolLifeBarComponent, e)->health = 10.0f;

		if (i == 0)
		{
			SignatureManager::get().printSignatureEntity(e);
			SDL_Log("%d", (int)SignatureManager::get().isThereTypeCmp(e, getIndexFromType<PlayerBattleComponent>()));
		}

		if (i != 0)
		{
			BattleMoveSystem::applyForce(e, { -30.0f, 0.0f });
		}
	}
	///Init test for Battle Phase



	///Init PhaseHandler
	world->phaseHandler.addPhaseBack(PhaseType::Exploring, StatePhase::On);
	///Init PhaseHandler



	SDL_Log("Ended creation");



	//Init all system
	CameraSystem::init();

	AnimationSystem::init();

	EnemySystem::init();
	//Init all system
	///FOR TESTING
}



void Game::init()
{
	//Init principle reference to Game class
	Game::sGameInstance = this;
	//Init principle reference to Game class



	//Initialization of enviroment
	SDL_Log("STARTING INITIALIZATION:");
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) )
	{
		SDL_Log("ERROR DURING SDL ENVIROMENT INITIALIZATION: %s", SDL_GetError());
		exit(1);
	}
	SDL_Log("\t-Succes initialization of SDL Enviroment");
	//Initialization of enviroment
	


	//Init other enviroment
	WindowHandler::get();

	TextureHandler::get();
	//Init other enviroment



	SDL_Log("\t-Initialization ended without problems");
	SDL_Log("");
}



bool Game::isInBattle()
{
	return world->phaseHandler.isTherePhase(PhaseType::Battle) != world->phaseHandler.Nphases();
}



void Game::startBattle()
{
	//Set the PhaseHandler
	world->phaseHandler.addPhaseBack(PhaseType::Battle, StatePhase::On);
	world->phaseHandler.setStatePhase(PhaseType::Exploring, StatePhase::Paused);
	//Set the PhaseHandler



	//Set the CameraData for the camera
	world->backupExploringCameraData = world->cameraData;

	world->cameraData = world->backupBattleCameraData;
	//Set the CameraData for the camera
}



void Game::calcDeltaTime()
{
	//Update deltaTime
	mDeltaTime = ( SDL_GetTicks()  - mTicksCount) / 1000.0f;
	mTicksCount = static_cast<float>( SDL_GetTicks() );
	//Update deltaTime



	//Clamp value of deltaTime
	if (mDeltaTime > sMaxDeltaTime)
	{
		mDeltaTime = sMaxDeltaTime;
	}
	//Clamp value of deltaTime
}



void Game::sleep()
{
	if (mVsync)
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
}



void Game::shutdown()
{
	delete world;
}



Game* Game::get()
{
	return sGameInstance;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Game
//-----------------------------------------------------------------------------------------------------------------------------------------



//RUN METHOD
void run()
{
	Game* game = new Game();

	game->init();
	game->loadData();

	while (game->isRunning())
	{
		game->calcDeltaTime();
		game->processInput();
		game->update();
		game->generateOutput();
		game->sleep();
	}

	game->shutdown();
}
//RUN METHOD