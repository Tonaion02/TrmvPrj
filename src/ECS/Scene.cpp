#include "Game.h"

#include "SDL_Enviroment.h"

#include "ECS/SceneManager.h"
#include "ECS/Scene.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Scene
//-----------------------------------------------------------------------------------------------------------------------------------------
BaseScene::BaseScene(const std::string& name)
	:game(Game::get()), world(Game::get()->getWorld()), status(statusScene::RunningScene)
{
	SceneManager::get().addScene(name, this);
	SDL_Log("%s", name.c_str());
}



void BaseScene::setStatus(statusScene status)
{
	this->status = status;
}



void BaseScene::unRegisterEntity(Entity e)
{
	//ADD AN ASSERT ON ENTITY

	group.erase(e);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Scene
//-----------------------------------------------------------------------------------------------------------------------------------------