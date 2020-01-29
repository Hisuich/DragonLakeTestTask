#pragma once
#include <math.h>

class Point
{
public:
	float x;
	float y;

public:
	Point()
	{
		x = 0;
		y = 0;
	}
	
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	
	float getSqrMagnitude()
	{
		return x * x + y * y;
	}

	float getMagnitude()
	{
		return sqrt(x * x + y * y);
	}

	void normalize()
	{
		float magnitude = getMagnitude();
		x = x / magnitude;
		y = y / magnitude;
	}

	Point subs(Point point)
	{
		return Point(this->x - point.x, this->y - point.y);
	}

	Point mult(float value)
	{
		return Point(this->x * value, this->y * value);
	}

	Point div(float value)
	{
		return Point(this->x / value, this->y / value);
	}

	Point getNormalize()
	{
		float magnitude = getMagnitude();
		return Point(x / magnitude, y / magnitude);
	}
};