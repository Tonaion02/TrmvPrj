#pragma once

#include "Input/InputHandler.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//InputHandler interface
//-----------------------------------------------------------------------------------------------------------------------------------------
inline void updateInput()
{
	InputHandler::get().updateInput();
}



inline Vector2i getCursorPos()
{
	return InputHandler::get().getPosCursor();
}



inline bool getMouseButton(int button)
{
	return InputHandler::get().getMouseButton(button);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//InputHandler interface
//-----------------------------------------------------------------------------------------------------------------------------------------