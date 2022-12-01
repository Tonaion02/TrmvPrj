#pragma once

#include <array>

#include "utils/Math/Math.h"
#include "SDL_scancode.h"





class InputHandler
{
public:
	static InputHandler& get()
	{
		static InputHandler instance;
		return instance;
	}

	void updateInput();
	void consumeClick(SDL_Scancode scancode);
	void consumeClick(unsigned int button);

	Vector2i getPosCursor();
	bool getMouseButton(unsigned int button);
	bool isPressedKey(SDL_Scancode scancode);
	bool isReleasedKey(SDL_Scancode scancode);
	bool isResizedWindow();
	Vector2i getWindowSize();
	bool isQuitted();

protected:
	Vector2i cursor;
	std::array<bool, 3> mouseButtons;

	std::array<bool, SDL_NUM_SCANCODES> keyPressed;
	std::array<bool, SDL_NUM_SCANCODES> keyReleased;

	bool windowResized;
	Vector2i sizeWindow;

	bool quitButton;
};