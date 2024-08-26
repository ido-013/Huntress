#pragma once
#include "Size.h"

int PosToMapX(float x);
int PosToMapY(float y);
float MapToPosX(int ind);
float MapToPosY(int ind);

float GetSqDistance(float ax, float ay, float bx, float by);