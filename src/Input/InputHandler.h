#pragma once

#include <array>

#include "utils/Math/Vector2i.h"





class InputHandler
{
public:
	static InputHandler& get()
	{
		static InputHandler instance;
		return instance;
	}

	void updateInput();

	Vector2i getPosCursor();
	bool getMouseButton(int button);

protected:
	Vector2i cursor;
	std::array<bool, 3> mouseButtons;
};