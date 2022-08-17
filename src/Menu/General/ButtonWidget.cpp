#include "Menu/General/ButtonWidget.h"

#include "Menu/General/GeneralFunctionForGui.h"

#include "SDL_Enviroment.h"

#include "Input/Input.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ButtonWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
ButtonWidget::ButtonWidget(const Vector2i& pos, const Vector2i& dim, class DrawableWidget* drawableWidget)
	:DrawableWidget(pos, dim), drawableWidget(drawableWidget)
{

}



void ButtonWidget::update()
{
	Vector2i cursor = getCursorPos();
	if (isPointInRect(cursor, getPos(), getDim()) && getMouseButton(0))
		function();
}



void ButtonWidget::draw()
{
	drawableWidget->draw();
}



void ButtonWidget::setFunction(std::function<void()> f)
{ 
	function = f; 
}



void ButtonWidget::setPos(const Vector2i& pos)
{
	this->rect->x = pos.x;
	this->rect->y = pos.y;
	drawableWidget->setPos(pos);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ButtonWidget
//-----------------------------------------------------------------------------------------------------------------------------------------