#include "Game.h"

#include "World.h"

//Including enviroment
#include "Enviroment/WindowHandler.h"
//Including enviroment

#include "Data/Camera/Camera.h"

#include "Systems/CameraSystem.h"





void CameraSystem::init()
{
	World* world = Game::get()->getWorld();

	//Init base info about camera
	world->cameraData.adj = { 0.0f, 0.0f };
	world->cameraData.nTileToRender = { 20, 20 };
	world->cameraData.baseScale = 1.0f;
	world->cameraData.zoom = 311.0f;
	//Init base info about camera
}



void CameraSystem::updateCamera()
{
	World* world = Game::get()->getWorld();

	//Update position of Camera
	world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->camera]].pos
		=
		world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos;
	//Update position of Camera

	//1* test for basescale
	Vector2i screenDim = WindowHandler::get().getWindowDimension();
	Vector2i imageDim = world->currentLevel.tileSet.tileDim * world->cameraData.nTileToRender;

	float screenRatio = screenDim.x / (float)screenDim.y;
	float imageRatio = imageDim.x / (float)imageDim.y;

	Vector2f scaledImageDim = screenRatio > imageRatio ? Vector2f(imageDim.x * screenDim.x / (float)imageDim.y, (float)screenDim.y) : Vector2f((float)screenDim.x, imageDim.y * screenDim.x / (float)imageDim.x);
	world->cameraData.baseScale = std::max(scaledImageDim.x / (float)imageDim.x, scaledImageDim.y / (float)imageDim.y);
	//1* test for basescale

	int visibleSpaceDim = 2 * tan60 * world->cameraData.zoom;
	Vector2i discardSpace = { screenDim.x - visibleSpaceDim, screenDim.y - visibleSpaceDim };
	Vector2f scaleZoom = { screenDim.x / (float)visibleSpaceDim, (float)screenDim.y / visibleSpaceDim };
	world->cameraData.baseScale *= std::max(scaleZoom.x, scaleZoom.y);
	//world->cameraData.adj += { discardSpace.x / 2.0f, discardSpace.y / 2.0f };


	//1* test for tiletorender
	Vector2f pos = world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos;

	world->cameraData.startToRender = { (int)pos.x - world->cameraData.nTileToRender.x / 2,(int)pos.y - world->cameraData.nTileToRender.y / 2 };
	world->cameraData.endToRender = { (int)pos.x + world->cameraData.nTileToRender.x / 2 + 1,(int)pos.y + world->cameraData.nTileToRender.y / 2 + 1 };

	Vector2f scaledTileDim = (Vector2f)world->currentLevel.tileSet.tileDim * world->cameraData.baseScale;
	Vector2f realScaledImageDim = world->currentLevel.dim * scaledTileDim;
	pos = pos * world->currentLevel.tileSet.tileDim;
	pos = pos * world->cameraData.baseScale;


	
	if (world->cameraData.startToRender.x < 0)
	{
		world->cameraData.startToRender.x = 0;
		world->cameraData.endToRender.x = world->cameraData.nTileToRender.x;
		world->cameraData.adj.x = 0.0f;
	}
	else if (world->cameraData.endToRender.x >= world->currentLevel.dim.x)
	{
		world->cameraData.startToRender.x = world->currentLevel.dim.x - world->cameraData.nTileToRender.x;
		world->cameraData.endToRender.x = world->currentLevel.dim.x;
		world->cameraData.adj.x = screenDim.x - realScaledImageDim.x;
	}
	else
	{
		world->cameraData.adj.x = -((int)pos.x - screenDim.x / 2.0f);
	}
		
	if (world->cameraData.startToRender.y < 0)
	{
		world->cameraData.startToRender.y = 0;
		world->cameraData.endToRender.y = world->cameraData.nTileToRender.y;
		world->cameraData.adj.y = 0.0f;
	}
	else if (world->cameraData.endToRender.y >= world->currentLevel.dim.y)
	{
		world->cameraData.startToRender.y = world->currentLevel.dim.y - world->cameraData.nTileToRender.y;
		world->cameraData.endToRender.y = world->currentLevel.dim.y;
		world->cameraData.adj.y = screenDim.y - realScaledImageDim.y;
	}
	else
	{
		world->cameraData.adj.y = -((int)pos.y - screenDim.y / 2.0f);
	}
	//1* test for tiletorender

	//1* test for visibleSpace
	//int visibleSpaceDim = 2 * tan60 * world->cameraData.zoom;
	//Vector2i discardSpace = { screenDim.x - visibleSpaceDim, screenDim.y - visibleSpaceDim };
	//Vector2f scaleZoom = { screenDim.x / (float)visibleSpaceDim, (float)screenDim.y / visibleSpaceDim };
	//world->cameraData.baseScale *= scaleZoom.y;
	//world->cameraData.adj += { discardSpace.x / 2.0f, discardSpace.y / 2.0f };
	//1* test for visibleSpace
}



void CameraSystem::recalculateBaseInfo()
{
	World* world = Game::get()->getWorld();

	//Take base info
	Vector2i screenDim = WindowHandler::get().getWindowDimension();
	int minDimension = std::min(screenDim.x, screenDim.y);
	//Take base info
}