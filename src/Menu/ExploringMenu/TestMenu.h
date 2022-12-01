#pragma once

#include "utils/Math/Math.h"

#include "Menu/General/ContainerWidget.h"
#include "Menu/General/VerticalGroupWidget.h"





template<unsigned int NumChildrens>
class TestMenu : public ContainerWidget
{
public:
	TestMenu(class SizedWidget* background, class VerticalGroupWidget<NumChildrens>* verticalGroupWidget, const Vector2i& transformPos = { 0, 0 })
		:ContainerWidget(background, verticalGroupWidget, transformPos)
	{}

protected:
	class VerticalGroupWidget<NumChildrens>* verticalGroupWidget;
};