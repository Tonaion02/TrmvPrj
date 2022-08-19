#include "ECS/SceneManager.h"

#include "ECS/TypeManagerScenes.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class SceneManager
//-----------------------------------------------------------------------------------------------------------------------------------------
SceneManager::SceneManager()
	:currentScene(0)
{

}



void SceneManager::addScene(unsigned int typeScene, class BaseScene* newScene)
{
	scenes[typeScene] = newScene;
}



void SceneManager::activateScene(unsigned int typeScene)
{
	//ASSERT: controlla se la scene è stata aggiunta nella lista

	//ASSERT: controlla se la scene è già presente

	/*activeScenes.emplace(activeScenes.begin(), scenes[typeScene]);*/
	activeScenes.push_back(scenes[typeScene]);
}



void SceneManager::deActivateScene(unsigned int typeScene)
{
	activeScenes.erase(std::find(activeScenes.begin(), activeScenes.end(), scenes[typeScene]));
}



BaseScene* SceneManager::getCurrentScene()
{
	return activeScenes[currentScene];
}



void SceneManager::nextScene()
{
	currentScene++;
}



void SceneManager::resetIterator()
{
	currentScene = 0;
}



bool SceneManager::isEndedScenes()
{
	return currentScene >= activeScenes.size();
}



bool SceneManager::isActive(unsigned int typeScene)
{
	//ASSERT: Controll if the scenes is in the list

	BaseScene* scene = scenes[typeScene];

	auto f = std::find(activeScenes.begin(), activeScenes.end(), scene);

	if (f != activeScenes.end())
		return true;
	
	return false;
}



BaseScene* SceneManager::getScene(unsigned int typeScene)
{
	//ASSERT: Controll if the scenes is in the list

	return scenes[typeScene];
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class SceneManager
//----------------------------------------------------------------------------------------------------------------------------------------- 