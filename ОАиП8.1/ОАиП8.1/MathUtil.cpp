
#define _USE_MATH_DEFINES

#include "MathUtil.h"
#include <cmath>
#include <stdexcept>

int Sign(float number)
{
	if (std::isnan(number))
	{
		throw std::invalid_argument("recieved NaN value");
	}

	const float eps = 0.00000001f;
	float diff = fabs(number);

	if (diff <= eps)
	{
		return 0;
	}
	else if (number > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

float GetAngle(int sign, float cos)
{
	float arccos = acos(cos);

	return (sign >= 0 ? arccos : static_cast<float>(M_PI * 2 - arccos));
}
