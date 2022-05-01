#pragma once





class Vector2i;


class Vector2f
{
public:
	Vector2f(float x = 0.0f, float y = 0.0f);

	//Operator for conversion
	operator Vector2i();

	//Arithmetic operator overloading
	Vector2f operator+(const Vector2f& other) const;
	Vector2f operator-(const Vector2f& other) const;
	Vector2f operator*(const Vector2f& other) const;
	Vector2f operator/ (const Vector2f& other) const;
	Vector2f operator*(float a) const;
	Vector2f operator/(float a) const;

	//Minus operator overloading
	Vector2f operator-() const;

	//Composed Assignment operator
	void operator+=(const Vector2f& other);
	void operator-=(const Vector2f& other);
	void operator*=(const Vector2f& other);
	void operator/=(const Vector2f& other);

	//Methods for particular operation
	Vector2f abs() const;
	float lengthQuad() const;
	float length() const;
	Vector2f normal() const;
	void normalize();

public:
	float x, y;
};