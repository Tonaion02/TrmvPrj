#pragma once

#include <cmath>

#include "Vector2i.h"
#include "Vector2f.h"








//Constant value
const float Pi = 3.1415926535f;
const float Pi2 = Pi * 2;
//Constant value



//Some inline method for Vectors
inline Vector2f abs(const Vector2f& v) { return { std::abs(v.x), std::abs(v.y) }; }
inline float length(const Vector2f& v) { return sqrtf(v.x * v.x + v.y * v.y); }
inline float lengthQuad(const Vector2f& v) { return v.x * v.x + v.y * v.y; }
inline Vector2f normal(const Vector2f& v) { return { v.x / v.length(), v.y / v.length() }; }
inline Vector2i abs(const Vector2i& v) { return { std::abs(v.x), std::abs(v.y) }; }
inline float length(const Vector2i& v) { return sqrtf(static_cast<float>(v.x * v.x + v.y * v.y)); }
inline float lengthQuad(const Vector2i& v) { return static_cast<float>(v.x * v.x + v.y * v.y); }
//Some inline method for Vectors



//Some inline method for Goniometry
inline float ToDegree(float radians) { return radians * 180.0f / Pi; }
inline float ToRadians(float degree) { return degree * Pi / 180.0f; }
//Some inline method for Goniometry



//Method for random generator of numbers
void setRandomGenerator(unsigned int seed);
int random();
//Method for random generator of numbers