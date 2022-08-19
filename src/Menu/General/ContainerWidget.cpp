#include "Menu/General/ContainerWidget.h"

#include "SDL_Enviroment.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ContainerWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
ContainerWidget::ContainerWidget(class SizedWidget* background, class SizedWidget* child, const Vector2i& transformPosChild)
	:SizedWidget(background->getPos(), background->getDim()), child(child), background(background), transformPosChild(transformPosChild)
{
	child->setPos(this->getPos() + transformPosChild);
}



void ContainerWidget::init()
{
	if(background)
		background->init();

	if(child)
		child->init();
}



void ContainerWidget::update()
{
	if(child)
		child->update();
}



void ContainerWidget::draw()
{
	if (background)
		background->draw();

	if (child)
		child->draw();
}



void ContainerWidget::setPos(const Vector2i& pos)
{
	this->rect->x = pos.x;
	this->rect->y = pos.y;

	background->setPos(pos);
	child->setPos(pos + transformPosChild);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ContainerWidget
//-----------------------------------------------------------------------------------------------------------------------------------------