#pragma once

#include "utils/Math/Math.h"
#include "utils/Math/Math.h"





template<typename T>
class Rect
{
public:
	Rect(T x, T y, T w, T h)
		:x(x), y(y), w(w), h(h)
	{}



public:
	T x, y, w, h;
};