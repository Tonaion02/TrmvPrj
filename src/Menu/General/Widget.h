#pragma once





class Widget
{
public:
	Widget() {}

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};