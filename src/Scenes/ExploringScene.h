#pragma once

#include <map>

#include "ECS/Scene.h"





class ExploringScene : public BaseScene
{
public:
	explicit ExploringScene();

	void loadScene() override;
	void updateScene() override;
	void generateOutputScene() override;
	void processInputScene() override;

protected:

public:
	std::map<std::string, struct XMLvariab*> templatesUniqueTile;
};