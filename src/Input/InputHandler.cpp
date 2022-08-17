#include "Input/InputHandler.h"

#include "SDL_Enviroment.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class InputHandler
//-----------------------------------------------------------------------------------------------------------------------------------------
void InputHandler::updateInput()
{
	Uint32 buttons = SDL_GetMouseState(&cursor.x, &cursor.y);

	for (int i = 0; i < mouseButtons.size(); i++)
		mouseButtons[i] = false;

	if ((buttons & SDL_BUTTON_LMASK) != 0)
		mouseButtons[0] = true;
	if ((buttons & SDL_BUTTON_MMASK) != 0)
		mouseButtons[1] = true;
	if ((buttons & SDL_BUTTON_RMASK) != 0)
		mouseButtons[2] = true;
}



Vector2i InputHandler::getPosCursor()
{
	return cursor;
}



bool InputHandler::getMouseButton(int button)
{
	return mouseButtons[button];
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class InputHandler
//-----------------------------------------------------------------------------------------------------------------------------------------