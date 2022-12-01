#pragma once

#include <cmath>

#include "utils/PersonalAssert.h"





template<typename T>
class Vector2
{
public:
	Vector2()
		:x(0), y(0)
	{}

	Vector2(T x, T y)
		:x(x), y(y)
	{}

	template<typename V>
	Vector2(const Vector2<V>& other)
	{
		this->x = static_cast<T>(other.x);
		this->y = static_cast<T>(other.y);
	}

	//template<typename V>
	//operator Vector2<V>();

	template<typename V>
	Vector2<V> cast()
	{
		return Vector2<V>(static_cast<V>(x), static_cast<V>(y));
	}

	//Operator 
	Vector2<T> operator+(const Vector2<T>& other) const
	{
		return Vector2<T>(other.x + this->x, other.y + this->y);
	}
	Vector2<T> operator-(const Vector2<T>& other) const
	{
		return Vector2<T>(this->x - other.x, this->y - other.y);
	}
	Vector2<T> operator*(const Vector2<T>& other) const
	{
		return Vector2<T>(this->x * other.x, this->y * other.y);
	}
	Vector2<T> operator/(const Vector2<T>& other) const
	{
		ASSERT(other.x != 0 && other.y != 0);
		return Vector2<T>(this->x / other.x, this->y / other.y);
	}
	Vector2<T> operator/(float a) const
	{
		ASSERT(a != 0);
		return Vector2<T>(static_cast<T>(this->x / a), static_cast<T>(this->y / a));
	}
	Vector2<T> operator*(float a) const
	{
		return Vector2<T>(static_cast<T>(this->x * a), static_cast<T>(this->y * a));
	}

	Vector2<T> operator-() const
	{
		return Vector2<T>(-this.x, -this.y);
	}

	//Composed Assignment operator
	void operator+=(const Vector2<T>& other)
	{
		this->x += other.x;
		this->y += other.y;
	}
	void operator-=(const Vector2<T>& other)
	{
		this->x -= other.x;
		this->y -= other.y;
	}
	void operator*=(const Vector2<T>& other)
	{
		this->x *= other.x;
		this->y *= other.y;
	}
	void operator/=(const Vector2<T>& other)
	{
		ASSERT(other.x != 0 && other.y != 0);
		this->x /= other.x;
		this->y /= other.y;
	}

	//Methods Particular operation
	Vector2<T> abs() const
	{
		return Vector2<T>(std::abs(x), std::abs(y));
	}
	T lengthQuad() const
	{
		return x * x + y * y;
	}
	float length() const
	{
		return sqrtf((float)(x * x + y * y));
	}

public:
	T x;
	T y;
};


//template<>
//class Vector2<int>
//{
//public:
//	template<>
//	operator Vector2<float>()
//	{
//
//	}
//};