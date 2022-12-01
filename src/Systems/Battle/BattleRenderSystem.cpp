#include "BattleRenderSystem.h"

//Including some context
#include "Game.h"
#include "World.h"
//Including some context

//Including basic ECS
#include "ECS/ComponentPool.h"
#include "ECS/ECS.h"
//Including basic ECS

//Including some Enviroment
#include "Enviroment/WindowHandler.h"
//Including some Enviroment





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class BattleRenderSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void BattleRenderSystem::init()
{

}



void BattleRenderSystem::draw()
{
	World* world = Game::get()->getWorld();

	SDL_Rect destRect;
	///It's better to add a separate texture for Actor
	destRect.w = static_cast<int>(world->currentLevel.battleCamp.tileSet.tileDim.x * world->cameraData.baseScale);
	destRect.h = static_cast<int>(world->currentLevel.battleCamp.tileSet.tileDim.y * world->cameraData.baseScale);


	SDL_Renderer* renderer = WindowHandler::get().getRenderer();

	ComponentPool<DrawBattleComponent>& drawBattleCmp = world->mPoolDrawBattleComponent;
	ComponentPool<TransformBattleComponent>& transformBattleCmp = world->mPoolTransformBattleComponent;

	Vector2i dim = world->currentLevel.battleCamp.dim;



	//Draw the battleCamp
	for (int y = world->cameraData.startToRender.y; y < world->cameraData.endToRender.y; y++)
	{
		destRect.y = static_cast<int>(y * destRect.h);
		destRect.y += static_cast<int>(world->cameraData.adj.y);

		for (int x = world->cameraData.startToRender.x; x < world->cameraData.endToRender.x; x++)
		{
			destRect.x = static_cast<int>(x * destRect.w);
			destRect.x += static_cast<int>(world->cameraData.adj.x);

			int id = world->currentLevel.battleCamp.graphicTileLayer.gTiles[y * dim.x + x];

			SDL_RenderCopy(
				renderer,
				world->currentLevel.battleCamp.tileSet.texture,
				&world->currentLevel.battleCamp.tileSet.srcRects[id],
				&destRect
			);
		}
	}
	//Draw the battleCamp



	//Draw all drawCmp
	for (unsigned int i = 0; i < drawBattleCmp.mNext; i++)
	{
		Entity e = drawBattleCmp.mDirectArray[i];
		TileSet* currentTileSet = getCmpIndex(world->mPoolDrawBattleComponent, i).tileSet;

		destRect.w = static_cast<int>(getCmpIndex(world->mPoolDrawBattleComponent, i).dim.x * world->cameraData.baseScale);
		destRect.h = static_cast<int>(getCmpIndex(world->mPoolDrawBattleComponent, i).dim.y * world->cameraData.baseScale);

		destRect.x = static_cast<int>(getCmpEntity(world->mPoolTransformBattleComponent, e).pos.x * world->cameraData.baseScale);
		destRect.y = static_cast<int>(getCmpEntity(world->mPoolTransformBattleComponent, e).pos.y * world->cameraData.baseScale);

		destRect.x += static_cast<int>(world->cameraData.adj.x);
		destRect.y += static_cast<int>(world->cameraData.adj.y);

		SDL_RenderCopy(
			renderer,
			currentTileSet->texture,
			&currentTileSet->srcRects[getCmpIndex(drawBattleCmp, i).id],
			&destRect
		);
	}
	//Draw all drawCmp
}



void BattleRenderSystem::drawColliders()
{
	World* world = Game::get()->getWorld();

	SDL_Rect destRect;

	SDL_Renderer* renderer = WindowHandler::get().getRenderer();

	ComponentPool<RectColliderComponent>& rectColliderCmp = world->mPoolRectColliderComponent;
	ComponentPool<DrawBattleComponent>& drawBattleCmp = world->mPoolDrawBattleComponent;
	ComponentPool<TransformBattleComponent>& transformBattleCmp = world->mPoolTransformBattleComponent;

	//Draw all colliders
	for (unsigned int i = 0; i < rectColliderCmp.mNext; i++)
	{
		Entity e = rectColliderCmp.mDirectArray[i];

		destRect.w = static_cast<int>(getCmpEntity(world->mPoolRectColliderComponent, e).dim.x * world->cameraData.baseScale);
		destRect.h = static_cast<int>(getCmpEntity(world->mPoolRectColliderComponent, e).dim.y * world->cameraData.baseScale);

		destRect.x = static_cast<int>(transformBattleCmp.mPackedArray[transformBattleCmp.mReverseArray[e]].pos.x * world->cameraData.baseScale);
		destRect.y = static_cast<int>(transformBattleCmp.mPackedArray[transformBattleCmp.mReverseArray[e]].pos.y * world->cameraData.baseScale);

		destRect.x += static_cast<int>(world->cameraData.adj.x);
		destRect.y += static_cast<int>(world->cameraData.adj.y);

		if(world->entitiesInCollisions.find(e) != world->entitiesInCollisions.end() )
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		else
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderDrawRect(renderer, &destRect);
	}
	//Draw all colliders
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class BattleRenderSystem
//-----------------------------------------------------------------------------------------------------------------------------------------