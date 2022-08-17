#include "Menu/General/DrawableWidget.h"

#include "SDL_Enviroment.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class DrawableWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
DrawableWidget::DrawableWidget(const Vector2i& pos, const Vector2i& dim)
	:rect(new SDL_Rect())
{
	rect->x = pos.x;
	rect->y = pos.y;
	rect->w = dim.x;
	rect->h = dim.y;
}



void DrawableWidget::setPos(const Vector2i& pos)
{
	rect->x = pos.x;
	rect->y = pos.y;
}



void DrawableWidget::setDim(const Vector2i& dim)
{
	rect->w = dim.x;
	rect->h = dim.y;
}



Vector2i DrawableWidget::getPos() const
{
	return Vector2i(rect->x, rect->y);
}



Vector2i DrawableWidget::getDim() const
{
	return Vector2i(rect->w, rect->h);
}



SDL_Rect* DrawableWidget::getRect()
{
	return rect;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class DrawableWidget
//-----------------------------------------------------------------------------------------------------------------------------------------