#include "Scenes/GeneralMenuScene.h"

//Including ECS
#include "ECS/ECS.h"
//Including ECS

//Including some context
#include "World.h"
#include "Game.h"
//Including some context

//Including systems
#include "Systems/Exploring/CameraSystem.h"
//Including systems

///TESTING MENU
//Including some Enviroments
#include "Enviroment/Input/Input.h"

#include "Enviroment/TextureHandler.h"
#include "Enviroment/WindowHandler.h"
//Including some Enviroments

//Including something about Menu
#include "Menu/General/ImageWidget.h"
#include "Menu/General/ColorSurfaceWidget.h"
#include "Menu/General/ContainerWidget.h"
#include "Menu/General/ButtonWidget.h"
#include "Menu/ExploringMenu/GeneralExploringMenu.h"
#include "Menu/ExploringMenu/TestMenu.h"
//Including something about Menu
///TESTING MENU





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class GeneralMenuScene
//-----------------------------------------------------------------------------------------------------------------------------------------
GeneralMenuScene::GeneralMenuScene()
	:BaseScene(idTypeScenes<GeneralMenuScene>())
{

}



void GeneralMenuScene::loadScene()
{
	choice = -1;

	///FOR TESTING

	///Creating menu
	std::array<SizedWidget*, LIMITS_CHILDREN_TEST_MENU> buttons;
	for (int i = 0; i < buttons.size(); i++)
	{
		ColorSurfaceWidget* background = new ColorSurfaceWidget(Vector2i(0, 0), Vector2i(200, 100), { 255, 0, 0, 255 });
		background->init();
		//ImageWidget* child = new ImageWidget(TextureHandler::get().getTexture("data/player.png"), Vector2i(0, 0), Vector2i(40, 40));
		//child->init();
		ColorSurfaceWidget* child = new ColorSurfaceWidget(Vector2i(0, 0), Vector2i(40, 40), { 0, 0, 255, 255 });
		child->init();
		ContainerWidget* container = new ContainerWidget(background, child, Vector2i(20, 5));
		container->init();



		ButtonWidget* button = new ButtonWidget(container);
		button->init();
		button->setFunction(changePage);
		buttons[i] = button;



		SizedWidget* sizedWidget = new SizedWidget({ 0, 0 }, { 0, 20 });
		sizedWidget->init();
		i++;
		buttons[i] = sizedWidget;
	}
	VerticalGroupWidget<LIMITS_CHILDREN_TEST_MENU>* vGroup = new VerticalGroupWidget<LIMITS_CHILDREN_TEST_MENU>({ 0, 0 }, buttons);
	vGroup->init();

	//ImageWidget* backgroundForMenu = new ImageWidget(TextureHandler::get().getTexture("data/buch-outdoor.png"), Vector2i(0, 0), Vector2i(500, 500));
	//backgroundForMenu->init();
	ColorSurfaceWidget* backgroundForMenu = new ColorSurfaceWidget(Vector2i(0, 0), Vector2i(600, 600), { 0, 255, 0, 255 });
	backgroundForMenu->init();
	TestMenu<LIMITS_CHILDREN_TEST_MENU>* ptr = new TestMenu<LIMITS_CHILDREN_TEST_MENU>(backgroundForMenu, vGroup, { backgroundForMenu->getDim().x / 2 - (buttons[0]->getDim().x / 2), 50 });
	ptr->init();
	widget = ptr;



	///TRYING TO MOVE MENU
	widget->setPos({ WindowHandler::get().getWindowDimension().x / 2 - (widget->getDim().x / 2), 100 });
	///TRYING TO MOVE MENU

	///Creating menu

	///FOR TESTING
}



void GeneralMenuScene::updateScene()
{
	widget->setPos({ WindowHandler::get().getWindowDimension().x / 2 - (widget->getDim().x / 2), 100 });
	widget->update();
}



void GeneralMenuScene::generateOutputScene()
{
	widget->draw();
}



void GeneralMenuScene::processInputScene()
{
	if (isResizedWindow())
	{
		SDL_Log("Window size changed to %dx%d", getWindowSize().x, getWindowSize().y);
		WindowHandler::get().updateWindowDimension(getWindowSize());
		CameraSystem::onUpdateWindowSize();
	}
	if (isQuitted())
	{
		Game::get()->setRunning(false);
	}



	if (isPressedKey(SDL_SCANCODE_M))
	{
		consumeClick(SDL_SCANCODE_M);
		Game::get()->endGeneralMenu();
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class GeneralMenuScene
//-----------------------------------------------------------------------------------------------------------------------------------------