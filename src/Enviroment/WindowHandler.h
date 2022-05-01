#pragma once

#include "utils/Math/Math.h"

#include "SDL_Enviroment.h"





class WindowHandler
{
public:
	static WindowHandler& get()
	{
		static WindowHandler instance = WindowHandler();
		return instance;
	}

	void createWindow();
	void updateWindowDimension(const Vector2i& newWindowSize);

	//Encapsulation Part
	struct SDL_Renderer* getRenderer() { return mRenderer; }
	struct SDL_Window* getWindow() { return mWindow; }
	Vector2i getWindowDimension() const { return mWindowDimension; }
	//Encapsulation Part

protected:
	WindowHandler();
	//Add destructor

public:
	static const Vector2i sBaseWindowDimension;

protected:
	struct SDL_Renderer* mRenderer;
	struct SDL_Window* mWindow;

	Vector2i mWindowDimension;
};