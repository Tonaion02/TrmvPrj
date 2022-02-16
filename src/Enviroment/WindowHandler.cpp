#include <stdlib.h>

#include "WindowHandler.h"

#include "SDL_Enviroment.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class WindowHandler
//-----------------------------------------------------------------------------------------------------------------------------------------
const Vector2i WindowHandler::sBaseWindowDimension = { 1080, 720 };



WindowHandler::WindowHandler()
	:mRenderer(nullptr),
	mWindow(nullptr),
	mWindowDimension(sBaseWindowDimension)
{
	this->createWindow();
}



void WindowHandler::createWindow()
{
	//Creation of the Window
	mWindow = SDL_CreateWindow("Testing", 100, 100, mWindowDimension.x, mWindowDimension.y, SDL_WINDOW_RESIZABLE);
	if (!mWindow)
	{
		SDL_Log("ERROR DURING CREATION OF THE WINDOW: %s", SDL_GetError());
		exit(1);
	}
	SDL_Log("\t-Successfully creation of the window");
	//Creation of the Window



	//Creation of the Renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (!mRenderer)
	{
		SDL_Log("ERROR DURING CREATION OF THE RENDERER: %s", SDL_GetError());
		exit(1);
	}
	SDL_Log("\t-Successfully creation of the renderer");
	//Creation of the Renderer
}



void WindowHandler::updateWindowDimension(const Vector2i& newWindowDimension)
{
	mWindowDimension = newWindowDimension;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class WindowHandler
//-----------------------------------------------------------------------------------------------------------------------------------------