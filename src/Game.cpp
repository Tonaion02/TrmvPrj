#include "Game.h"

#include "ECS/TypeManager.h"

//Including Some Utils
#include "Misc/Direction.h"
#include "Misc/Grid.h"

#include "utils/FromTypeToText.h"
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
#include "ECS/ECS.h"
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


///FOR TESTING
#include "ECS/Scene.h"

#include "Scenes/ExploringScene.h"
#include "Scenes/BattleScene.h"

#include "utils/Physic/DataGridSP.h"
#include "utils/Physic/GridSP.h"
///FOR TESTING





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Game
//-----------------------------------------------------------------------------------------------------------------------------------------
const float Game::sMaxDeltaTime = 0.5f;
Game* Game::sGameInstance = nullptr;





void Game::update()
{
	resetIteratorScene();

	while (!isEndedScenes())
	{
		BaseScene* current = currentScene();

		current->updateScene();

		nextScene();
	}
}



void Game::processInput()
{
	//General handling of the Input
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

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

	//General handling of the Input



	//ProcessInput for each scene
	resetIteratorScene();

	if (!isEndedScenes())
	{
		BaseScene* current = currentScene();

		current->processInputScene();
	}
	//ProcessInput for each scene
}



void Game::generateOutput()
{
	//Clean screen
	SDL_SetRenderDrawColor(WindowHandler::get().getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(WindowHandler::get().getRenderer());
	//Clean screen



	resetIteratorScene();

	while (!isEndedScenes())
	{
		BaseScene* current = currentScene();

		current->generateOutputScene();

		nextScene();
	}


	//Render elements
	SDL_RenderPresent(WindowHandler::get().getRenderer());
	//Render elements
}



void testFunction()
{
	SDL_Log("Wewe!!!!!");
}



void Game::loadData()
{
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



	//Create Scenes
	exploringScene = new ExploringScene();
	exploringScene->loadScene();
	battleScene = new BattleScene();
	battleScene->loadScene();
	activateScene<ExploringScene>();
	//Create Scenes



	//Load TileSet and Texture
	world->currentLevel.texture = TextureHandler::get().getTexture("data/buch-outdoor.png");
	world->mTileSetHandler.loadTileSet("data/buch-outdoor.png", 32);
	world->currentLevel.tileSet = world->mTileSetHandler.getTileSet("data/buch-outdoor.png");
	world->textureActor = TextureHandler::get().getTexture("data/player.png");
	world->mTileSetHandler.loadTileSet("data/player.png", 32);
	world->tilesetActor = world->mTileSetHandler.getTileSet("data/player.png");

	TextureHandler::get().loadTexture("data/brimstone.png");
	world->mTileSetHandler.loadTileSet("data/brimstone.png", 32);
	//Load TileSet and Texture



	//Load Level	
	world->currentLevel = levelWrapper("data/level0.tmx");
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
		registerEntity(&world->mPoolDrawComponent, e);
		getCmpEntity(&world->mPoolDrawComponent, e)->id = 17;

		if (e != 1)
		{
			TileSystem::registerPos({ (int)x,(int)x }, z, e);

			registerEntity(&world->mPoolMoveComponent, e);
			getCmpEntity(&world->mPoolMoveComponent, e)->currentDirection = NoneDirection;
			getCmpEntity(&world->mPoolMoveComponent, e)->lastDirection = Direction::Right;

			registerEntity(&world->mPoolActionComponent, e);
			getCmpEntity(&world->mPoolActionComponent, e)->currentAction = NoneActions;
			getCmpEntity(&world->mPoolActionComponent, e)->actionDelays[Actions::Walk].coolDown = 0.5f;
			getCmpEntity(&world->mPoolActionComponent, e)->actionDelays[Actions::Rotate].coolDown = 0.5f;

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
	///Init camera



	///Init test for Battle Phase
	int n = 2;
	bool first = true;
	Entity firstEntity;

	for (int i = 0; i < n; i++)
	{
		Entity e = EntityManager::get().createEntity();

		if (first)
		{
			firstEntity = e;
			first = false;
		}

		registerEntity(&world->mPoolTransformBattleComponent, e);
		if (i == 0)
		{
			world->mPoolTransformBattleComponent.mPackedArray[world->mPoolTransformBattleComponent.mReverseArray[e]].pos = { 80.0f, 1.0f };
			world->BattlePlayerEntity = e;
			registerEntity(&world->mPoolPlayerBattleComponent, e);

			world->delayFiring.coolDown = 0.5f;
			initTimer(&world->delayFiring);
			world->delayHitBox.coolDown = 0.05f;
			initTimer(&world->delayHitBox);
		}
		else
		{
			Vector2i pos = { random() % (world->currentLevel.battleCamp.dim.x * 16), random() % (world->currentLevel.battleCamp.dim.y * 16) };
			
			for (int j = 0, iteratorEntity = firstEntity; j < i; j++, iteratorEntity++)
			{
				TransformBattleComponent* transform = getCmpEntity(&world->mPoolTransformBattleComponent, iteratorEntity);
				if (ColliderSystem::detectCollision(pos, Vector2i(16, 16), transform->pos, {16, 16}))
				{
					pos = { random() % (world->currentLevel.battleCamp.dim.x * 16), random() % (world->currentLevel.battleCamp.dim.y * 16) };
					j = 0, iteratorEntity = firstEntity;
				}
			}
			
			getCmpEntity(&world->mPoolTransformBattleComponent, e)->pos = pos;
			registerEntity(&world->mPoolEnemyBattleComponent, e);
		}

		registerEntity(&world->mPoolControlledRectColliderComponent, e);

		registerEntity(&world->mPoolPhysicBoxComponent, e);
		getCmpEntity(&world->mPoolPhysicBoxComponent, e)->mass = 1.0f;
		getCmpEntity(&world->mPoolPhysicBoxComponent, e)->v = { 0.0f, 0.0f };
		
		registerEntity(&world->mPoolRectColliderComponent, e);
		getCmpEntity(&world->mPoolRectColliderComponent, e)->dim = { 16, 16 };
		
		registerEntity(&world->mPoolDrawBattleComponent, e);
		getCmpEntity(&world->mPoolDrawBattleComponent, e)->id = 17;
		getCmpEntity(&world->mPoolDrawBattleComponent, e)->tileSet = world->mTileSetHandler.getTileSet("data/player.png");
		getCmpEntity(&world->mPoolDrawBattleComponent, e)->dim = getCmpEntity(&world->mPoolDrawBattleComponent, e)->tileSet->tileDim;

		registerEntity(&world->mPoolDamageComponent, e);

		registerEntity(&world->mPoolLifeBarComponent, e);
		getCmpEntity(&world->mPoolLifeBarComponent, e)->health = 300.0f;

		//if (i != 0)
		//{
		//	BattleMoveSystem::applyForce(e, { -30.0f, 0.0f });
		//}



		//register Entity to GridSP for collision detection
		registerEntity(e, world->currentLevel.battleCamp.gridSP);
		//register Entity to GridSP for collision detection
	}
	///Init test for Battle Phase



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
	return isActiveScene<BattleScene>();
}



void Game::startBattle()
{
	//Push up the BattleScene
	getScene<ExploringScene>()->setStatus(statusScene::PauseScene);
	activateScene<BattleScene>();
	//Push up the BattleScene



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