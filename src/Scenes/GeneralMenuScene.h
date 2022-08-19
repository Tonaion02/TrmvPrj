#pragma once

#include "ECS/Scene.h"





class GeneralMenuScene : public BaseScene
{
public:
	GeneralMenuScene();

	void loadScene() override;
	void updateScene() override;
	void generateOutputScene() override;
	void processInputScene() override;

public:
	class SizedWidget* widget;
	int choice;

protected:
};