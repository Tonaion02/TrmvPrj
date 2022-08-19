#pragma once

#include <functional>

#include "Menu/General/SizedWidget.h"





class ButtonWidget : public SizedWidget
{
public:
	ButtonWidget(class SizedWidget* sizedWidget);

	virtual void init() override { }
	virtual void update() override;
	virtual void draw() override;

	void setFunction(std::function<void()> f);
	void setPos(const Vector2i& pos) override;

protected:
	class SizedWidget* sizedWidget;

	std::function<void()> function;
};