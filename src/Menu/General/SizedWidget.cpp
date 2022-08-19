#include "Menu/General/SizedWidget.h"

#include "SDL_Enviroment.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class DrawableWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
SizedWidget::SizedWidget(const Vector2i& pos, const Vector2i& dim)
	:rect(new SDL_Rect())
{
	rect->x = pos.x;
	rect->y = pos.y;
	rect->w = dim.x;
	rect->h = dim.y;
}



void SizedWidget::setPos(const Vector2i& pos)
{
	rect->x = pos.x;
	rect->y = pos.y;
}



void SizedWidget::setDim(const Vector2i& dim)
{
	rect->w = dim.x;
	rect->h = dim.y;
}



Vector2i SizedWidget::getPos() const
{
	return Vector2i(rect->x, rect->y);
}



Vector2i SizedWidget::getDim() const
{
	return Vector2i(rect->w, rect->h);
}



SDL_Rect* SizedWidget::getRect()
{
	return rect;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class DrawableWidget
//-----------------------------------------------------------------------------------------------------------------------------------------