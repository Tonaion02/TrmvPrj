#pragma once

#include "Menu/General/ContainerWidget.h"
#include "Menu/General/VerticalGroupWidget.h"





template<unsigned int NumChildrens>
class TestMenu : public ContainerWidget
{
public:
	TestMenu(class DrawableWidget* background, class VerticalGroupWidget<NumChildrens>* verticalGroupWidget)
		:ContainerWidget(background, verticalGroupWidget, {0, 0})
	{}

protected:
	class VerticalGroupWidget<NumChildrens>* verticalGroupWidget;
};