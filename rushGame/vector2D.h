#pragma once

struct vector2D
{
	float x, y;

	vector2D(float x, float y) : x(x), y(y) {}
	vector2D& operator+=(const vector2D& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
};

vector2D operator*(const vector2D& vec, float f);