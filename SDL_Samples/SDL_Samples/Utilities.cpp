#include "Utilities.h"

const float Utilities::PI =  3.14159265358979f;

float Utilities::DegreeToRadians(float degree)
{
	return degree * (PI / 180.0f);
}

float Utilities::RadiansToDegrees(float radians)
{
	return radians * (180.0f / PI);
}