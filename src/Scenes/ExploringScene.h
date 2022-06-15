#pragma once

#include "ECS/Scene.h"





class ExploringScene : public BaseScene
{
public:
	explicit ExploringScene();

	void updateScene() override;
	void generateOutputScene() override;
	void processInputScene() override;

protected:

public:
};