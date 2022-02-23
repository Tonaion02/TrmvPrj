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
	void input();
	void update();
	void generateOutput();
	void shutdown();
	//Principles Methods


public:
	//Secondary Methods
	bool isRunning() { return mIsRunning; }
	float getDeltaTime() { return mDeltaTime; }
	//Secondary Methods



	//Handling flow of the program
	void startBattle();
	void endBattle(); //TO ADD
	//Handling flow of the program



	//Encapsulation Methods
	inline struct World* getWorld() { return mWorld; }
	//Encapsulation Methods



	//Access to this class from everywhere
	static class Game* get();
	//Access to this class from everywhere
protected:
	bool mIsRunning;

	bool mVsync;

	float mDeltaTime;
	float mTicksCount;

	struct World* mWorld;

	static const float sMaxDeltaTime;
	static class Game* sGameInstance;
};