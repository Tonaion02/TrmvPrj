#pragma once





class Vector2f;

class Vector2i
{
public:
	Vector2i(int x = 0, int y = 0);

	//Operator for class conversion
	operator Vector2f();

	//Arithmetic operator overloading
	Vector2i operator+(const Vector2i& other) const;
	Vector2i operator-(const Vector2i& other) const;
	Vector2i operator*(const Vector2i& other) const;
	Vector2i operator/(const Vector2i& other) const;
	Vector2i operator/(float a) const;
	Vector2i operator*(int a) const;

	//Minus operator overloading
	Vector2i operator-() const;

	//Composed Assignment operator
	void operator+=(const Vector2i& other);
	void operator-=(const Vector2i& other);
	void operator*=(const Vector2i& other);
	void operator/=(const Vector2i& other);

	//Methods Particular operation
	Vector2i abs() const;
	float lengthQuad() const;
	float length() const;

public:
	int x, y;
};