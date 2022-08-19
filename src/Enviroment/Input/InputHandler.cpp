#include "Enviroment/Input/InputHandler.h"

#include "SDL_Enviroment.h"

#include "utils/PersonalAssert.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class InputHandler
//-----------------------------------------------------------------------------------------------------------------------------------------
void InputHandler::updateInput()
{
	keyPressed.fill(false);
	keyReleased.fill(false);
	
	quitButton = false;

	windowResized = false;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quitButton = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				windowResized = true;
				sizeWindow = { event.window.data1, event.window.data2 };
				break;

			default:
				break;
			}
			break;

		case SDL_KEYDOWN:
			keyPressed[event.key.keysym.scancode] = true;
			break;

		case SDL_KEYUP:
			keyReleased[event.key.keysym.scancode] = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseButtons[0] = true;
				break;
			case SDL_BUTTON_MIDDLE:
				mouseButtons[1] = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouseButtons[2] = true;
				break;

			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseButtons[0] = false;
				break;
			case SDL_BUTTON_MIDDLE:
				mouseButtons[1] = false;
				break;
			case SDL_BUTTON_RIGHT:
				mouseButtons[2] = false;
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}



	SDL_GetMouseState(&cursor.x, &cursor.y);
}



void InputHandler::consumeClick(SDL_Scancode scancode)
{
	keyPressed[scancode] = false;
}



void InputHandler::consumeClick(unsigned int button)
{
	ASSERT(button < 0 || button >= 3);

	mouseButtons[button] = false;
}



Vector2i InputHandler::getPosCursor()
{
	return cursor;
}



bool InputHandler::isResizedWindow()
{
	return windowResized;
}



Vector2i InputHandler::getWindowSize()
{
	return sizeWindow;
}



bool InputHandler::isQuitted()
{
	return quitButton;
}



bool InputHandler::getMouseButton(unsigned int button)
{
	ASSERT(button < 0 || button >= 3);

	return mouseButtons[button];
}



bool InputHandler::isPressedKey(SDL_Scancode scancode)
{
	return keyPressed[scancode];
}



bool InputHandler::isReleasedKey(SDL_Scancode scancode)
{
	return keyReleased[scancode];
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class InputHandler
//-----------------------------------------------------------------------------------------------------------------------------------------