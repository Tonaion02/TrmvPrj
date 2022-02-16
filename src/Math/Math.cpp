#include <stdio.h>
#include <cmath>

#include "Math.h"





//Class Vector2i
Vector2i::Vector2i(int x, int y)
	:x(x), y(y)
{

}



Vector2i::Vector2i(const Vector2f& other)
	:x(static_cast<int>(other.x)), y(static_cast<int>(other.y))
{
	
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



Vector2f Vector2i::operator/(const Vector2f& other) const
{
	return Vector2f(this->x / other.x, this->y / other.y);
}



Vector2i Vector2i::operator/(const Vector2i& other) const
{
	return Vector2i(this->x / other.x, this->y / other.y);
}



Vector2i Vector2i::operator/(float a) const
{
	return Vector2i(static_cast<int>(this->x / a), static_cast<int>(this->y / a));
}



Vector2i Vector2i::operator-() const
{
	return Vector2f(static_cast<float>(-this->x), static_cast<float>(-this->y));
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



//void Vector2i::operator*=(const Vector2i& other)
//{
//	this->x *= other.x;
//	this->y *= other.y;
//}
//
//
//
//void Vector2i::operator/=(const Vector2i& other)
//{
//	this->x /= other.x;
//	this->y /= other.y;
//}
//Class Vector2i





//Class Vector2f
Vector2f::Vector2f(float x, float y)
	:x(x), y(y)
{

}



Vector2f::Vector2f(const Vector2i& other)
	:x(static_cast<float>(other.x)), y(static_cast<float>(other.y))
{
	
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



Vector2f Vector2f::operator/(float a) const
{
	return Vector2f(this->x / a, this->y / a);
}
//
//
//
//Vector2f Vector2f::operator/(const Vector2f& other) const
//{
//	return Vector2f(this->x / other.x, this->y / other.y);
//}



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



//void Vector2f::operator*=(const Vector2f& other)
//{
//	this->x *= other.x;
//	this->y *= other.y;
//}
//
//
//
//void Vector2f::operator/=(const Vector2f& other)
//{
//	this->x /= other.x;
//	this->y /= other.y;
//}



Vector2f Vector2f::operator*(float a) const
{
	return Vector2f(this->x * a, this->y * a);
}
//Class Vector2f











Vector2f abs(const Vector2f& v)
{
	return { std::abs(v.x), std::abs(v.y) };
}


Vector2i abs(const Vector2i& v)
{
	return { std::abs(v.x), std::abs(v.y) };
}