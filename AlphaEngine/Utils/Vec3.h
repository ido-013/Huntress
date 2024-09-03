#pragma once
#include "AEMath.h"

struct Vec3
{
	float x;
	float y;
	float z;

	friend Vec3 operator*(const AEMtx33& mat, const Vec3& vec);
};