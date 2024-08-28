// Author : sinu

#include "Projectile.h"

float vxt(float t, float vx0, float ax)
{
	return vx0 + ax * t;
}

float vyt(float t, float vy0, float ay) 
{
	return vy0 + ay * t;
}

float integrate_x(float init, float fin, float dt, float a, float v0)
{
	float out = 0.0;
	for (float t = init; t < fin; t += dt) {
		out += vxt(t, v0, a) * dt;
	}
	return out;
}

float integrate_y(float init, float fin, float dt, float a, float v0)
{
	float out = 0.0;
	for (float t = init; t < fin; t += dt) {
		out += vyt(t, v0, a) * dt;
	}
	return out;
}
