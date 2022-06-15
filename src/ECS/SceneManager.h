#pragma once

#include <string>
#include <vector>
#include <map>





//ADD A MAX TO SCENES
class SceneManager
{
public:
	static SceneManager& get()
	{
		static SceneManager instance;
		return instance;
	}

	void addScene(const std::string& nameScene, class BaseScene* newScene);
	void activateScene(const std::string& nameScene);
	void deactivateScene(const std::string& nameScene);

	class BaseScene* getCurrentScene();
	void nextScene();
	void resetIterator();
	bool isEndedScenes();

	bool isActive(class BaseScene* scene);
	class BaseScene* getScene(const std::string& nameScene);

protected:
	SceneManager();

protected:
	std::map<const std::string, BaseScene*> scenes;
	std::vector<class BaseScene*> activeScenes;
	unsigned int currentScene;
};