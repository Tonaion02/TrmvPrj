#include <cmath>

#include "utils/PersonalAssert.h"

#include "Vector2i.h"
#include "Vector2f.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Vector2i
//-----------------------------------------------------------------------------------------------------------------------------------------
Vector2i::Vector2i(int x, int y)
	:x(x), y(y)
{

}



Vector2i::operator Vector2f()
{
	return Vector2f(static_cast<float>(x), static_cast<float>(y));
}



Vector2i Vector2i::operator+(const Vector2i& other) const
{
	return Vector2i(this->x + other.x, this->y + other.y);
}



Vector2i Vector2i::operator-(const Vector2i& other) const
{
	return Vector2i(this->x - other.x, this->y - other.x);
}



Vector2i Vector2i::operator*(const Vector2i& other) const
{
	return Vector2i(this->x * other.x, this->y * other.y);
}



Vector2i Vector2i::operator*(int a) const
{
	return Vector2i(this->x * a, this->y * a);
}



Vector2i Vector2i::operator/(float a) const
{
	ASSERT(a != 0);

	return Vector2i(static_cast<int>(this->x / a), static_cast<int>(this->y / a));
}



Vector2i Vector2i::operator/(const Vector2i& other) const
{
	ASSERT(other.x != 0 && other.y != 0);

	return Vector2i(this->x / other.x, this->y / other.y);
}



Vector2i Vector2i::operator-() const
{
	return Vector2i(-this->x, -this->y);
}



void Vector2i::operator+=(const Vector2i& other)
{
	this->x += other.x;
	this->y += other.y;
}



void Vector2i::operator-=(const Vector2i& other)
{
	this->x -= other.x;
	this->y -= other.y;
}



void Vector2i::operator*=(const Vector2i& other)
{
	this->x *= other.x;
	this->y *= other.y;
}



void Vector2i::operator/=(const Vector2i& other)
{
	ASSERT(other.x != 0 && other.y != 0);

	this->x /= other.x;
	this->y /= other.y;
}



Vector2i Vector2i::abs() const
{
	return { std::abs(x), std::abs(y) };
}



float Vector2i::lengthQuad() const
{
	return static_cast<float>(x * x + y * y);
}



float Vector2i::length() const
{
	return sqrtf(static_cast<float>(x * x + y * y));
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Vector2i
//-----------------------------------------------------------------------------------------------------------------------------------------