#include <cmath>

#include "utils/PersonalAssert.h"

#include "Vector2f.h"
#include "Vector2i.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Vector2f
//-----------------------------------------------------------------------------------------------------------------------------------------
Vector2f::Vector2f(float x, float y)
	:x(x), y(y)
{

}



Vector2f::operator Vector2i()
{
	return Vector2i(static_cast<int>(x), static_cast<int>(y));
}



Vector2f Vector2f::operator+(const Vector2f& other) const
{
	return Vector2f(this->x + other.x, this->y + other.y);
}



Vector2f Vector2f::operator-(const Vector2f& other) const
{
	return Vector2f(this->x - other.x, this->y - other.y);
}



Vector2f Vector2f::operator*(const Vector2f& other) const
{
	return Vector2f(this->x * other.x, this->y * other.y);
}



Vector2f Vector2f::operator*(float a) const
{
	return Vector2f(this->x * a, this->y * a);
}



Vector2f Vector2f::operator/(float a) const
{
	ASSERT(a != 0);

	return Vector2f(this->x / a, this->y / a);
}



Vector2f Vector2f::operator/(const Vector2f& other) const
{
	ASSERT(other.x != 0 && other.y != 0);

	return Vector2f(this->x / other.x, this->y / other.y);
}



Vector2f Vector2f::operator-() const
{
	return Vector2f(-this->x, -this->y);
}



void Vector2f::operator+=(const Vector2f& other)
{
	this->x += other.x;
	this->y += other.y;
}



void Vector2f::operator-=(const Vector2f& other)
{
	this->x -= other.x;
	this->y -= other.y;
}



void Vector2f::operator*=(const Vector2f& other)
{
	this->x *= other.x;
	this->y *= other.y;
}



void Vector2f::operator/=(const Vector2f& other)
{
	ASSERT(other.x != 0 && other.y != 0);

	this->x /= other.x;
	this->y /= other.y;
}



Vector2f Vector2f::abs() const
{
	return { std::abs(x), std::abs(y) };
}



float Vector2f::lengthQuad() const
{
	return x * x + y * y;
}



float Vector2f::length() const
{
	return sqrtf(x * x + y * y);
}



Vector2f Vector2f::normal() const
{
	ASSERT(x != 0.0f || y != 0.0f);

	Vector2f direction;
	float length = this->length();

	if (x != 0.0f)
		direction.x = x / length;
	if (y != 0.0f)
		direction.y = y / length;

	return direction;
}



void Vector2f::normalize()
{
	ASSERT(x != 0.0f || y != 0.0f);

	float length = this->length();

	if (x != 0.0f)
		x /= length;
	if (y != 0.0f)
		y /= length;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Vector2f
//-----------------------------------------------------------------------------------------------------------------------------------------