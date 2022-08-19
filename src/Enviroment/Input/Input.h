#pragma once

#include "Enviroment/Input/InputHandler.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//InputHandler interface
//-----------------------------------------------------------------------------------------------------------------------------------------
inline void updateInput()
{
	InputHandler::get().updateInput();
}



inline void consumeClick(unsigned int button)
{
	InputHandler::get().consumeClick(button);
}



inline void consumeClick(SDL_Scancode scancode)
{
	InputHandler::get().consumeClick(scancode);
}



inline Vector2i getCursorPos()
{
	return InputHandler::get().getPosCursor();
}



inline bool getMouseButton(unsigned int button)
{
	return InputHandler::get().getMouseButton(button);
}



inline bool isPressedKey(SDL_Scancode scancode)
{
	return InputHandler::get().isPressedKey(scancode);
}



inline bool isReleasedKey(SDL_Scancode scancode)
{
	return InputHandler::get().isReleasedKey(scancode);
}



inline bool isResizedWindow()
{
	return InputHandler::get().isResizedWindow();
}



inline Vector2i getWindowSize()
{
	return InputHandler::get().getWindowSize();
}



inline bool isQuitted()
{
	return InputHandler::get().isQuitted();
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//InputHandler interface
//-----------------------------------------------------------------------------------------------------------------------------------------