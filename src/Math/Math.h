#pragma once





class Vector2f;
class Vector2i
{
public:
	Vector2i(int x = 0, int y = 0);

	//Copy constructor from a float vector
	Vector2i(const Vector2f& other);

	//Arithmetic operator overloading
	Vector2i operator+(const Vector2i& other) const;
	Vector2i operator-(const Vector2i& other) const;
	Vector2i operator*(const Vector2i& other) const;
	Vector2f operator/(const Vector2f& other) const;
	Vector2i operator/(const Vector2i& other) const;
	Vector2i operator/(float a) const;
	Vector2i operator*(int a) const;
	
	//Minus operator overloading
	Vector2i operator-() const;
	
	//Composed Assignment operator
	void operator+=(const Vector2i& other);
	void operator-=(const Vector2i& other);
	//void operator*=(const Vector2i& other);
	//void operator/=(const Vector2i& other);

public:
	int x, y;
};





class Vector2f
{
public:
	Vector2f(float x = 0.0f, float y = 0.0f);

	//Copy constructor from a integer vector
	Vector2f(const Vector2i& other);

	//Arithmetic operator overloading
	Vector2f operator+(const Vector2f& other) const;
	Vector2f operator-(const Vector2f& other) const;
	Vector2f operator*(const Vector2f& other) const;
	Vector2f operator*(float a) const;
	Vector2f operator/(float a) const;
	//Vector2f operator/(const Vector2f& other) const;

	//Minus operator overloading
	Vector2f operator-() const;
	
	//Composed Assignment operator
	void operator+=(const Vector2f& other);
	void operator-=(const Vector2f& other);
	//void operator*=(const Vector2f& other);
	//void operator/=(const Vector2f& other);

public:
	float x, y;
};





Vector2f abs(const Vector2f& v);
Vector2i abs(const Vector2i& v);

const float tan60 = 1.732050808f;