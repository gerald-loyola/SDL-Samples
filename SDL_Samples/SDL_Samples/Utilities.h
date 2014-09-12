#pragma once

#ifndef __UTILITY__
#define __UTILITY__

namespace Utilities
{
	const float  PI = 3.14159265358979f;

	float DegreeToRadians(float degree)
	{
		return degree * (PI / 180.0f);
	}

	float RadiansToDegrees(float radians)
	{
		return radians * (180.0f / PI);
	}
}

#endif