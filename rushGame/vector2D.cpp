#include "vector2D.h"


vector2D operator*(const vector2D& vec, float f)
{
	return vector2D(vec.x * f, vec.y * f);
}
