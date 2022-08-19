#include "Menu/General/ButtonWidget.h"

#include "Menu/General/GeneralFunctionForGui.h"

#include "SDL_Enviroment.h"

#include "Enviroment/Input/Input.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ButtonWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
ButtonWidget::ButtonWidget(class SizedWidget* sizedWidget)
	:SizedWidget(sizedWidget->getPos(), sizedWidget->getDim()), sizedWidget(sizedWidget)
{

}



void ButtonWidget::update()
{
	Vector2i cursor = getCursorPos();

	if (isPointInRect(cursor, getPos(), getDim()) && getMouseButton(0))
	{
		function();
		consumeClick(0);
	}
}



void ButtonWidget::draw()
{
	sizedWidget->draw();
}



void ButtonWidget::setFunction(std::function<void()> f)
{ 
	function = f; 
}



void ButtonWidget::setPos(const Vector2i& pos)
{
	this->rect->x = pos.x;
	this->rect->y = pos.y;
	sizedWidget->setPos(pos);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ButtonWidget
//-----------------------------------------------------------------------------------------------------------------------------------------