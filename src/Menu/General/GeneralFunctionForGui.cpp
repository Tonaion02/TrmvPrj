#include "Menu/General/GeneralFunctionForGui.h"





bool isPointInRect(const Vector2i& pos, const Vector2i& posRect, const Vector2i& dimRect)
{
	return pos.x > posRect.x && pos.x < posRect.x + dimRect.x && pos.y > posRect.y && pos.y < posRect.y + dimRect.y;
}