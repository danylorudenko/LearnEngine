#include "..\Include\Math\MathUtil.h"

float DegreeToRad(const float degree)
{
	return PI_F * degree / 180;
}

float RadToDegree(float rad)
{
	return rad / PI_F * 180;
}