#pragma once

#include "SDL_Enviroment.h"





void run();

class Game
{
	friend void run();
protected:
	//Principles Methods
	void init();
	void loadData();
	void sleep();
	void calcDeltaTime();
	void processInput();
	void update();
	void generateOutput();
	void shutdown();
	//Principles Methods


public:
	//Secondary Methods
	bool isRunning() { return mIsRunning; }
	void setRunning(bool running) { mIsRunning = running; }
	float getDeltaTime() { return mDeltaTime; }
	bool isInBattle();
	bool isInGeneralMenu();
	//Secondary Methods



	//Handling flow of the program
	void startBattle();
	void endBattle(); ///TO ADD
	void startGeneralMenu();
	void endGeneralMenu();
	//Handling flow of the program



	//Encapsulation Methods
	inline struct World* getWorld() { return world; }
	inline class ExploringScene* getExploringScene() { return sExploringScene; }
	inline class BattleScene* getBattleScene() { return sBattleScene; }
	inline class GeneralMenuScene* getGeneraMenuScene() { return sGeneralMenuScene; }
	//Encapsulation Methods



	//Access to this class from everywhere
	static class Game* get();
	//Access to this class from everywhere
protected:
	bool mIsRunning;
	
	bool mVsync;

	bool mDebugMode;

	float mDeltaTime;
	float mTicksCount;

	struct World* world;

	static const float sMaxDeltaTime;
	static class Game* sGameInstance;
	class ExploringScene* sExploringScene;
	class BattleScene* sBattleScene;
	class GeneralMenuScene* sGeneralMenuScene;
};