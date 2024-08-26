#include "Utils.h"

int PosToMapX(float x)
{
    return (x + (windowWidth / 2)) / (windowWidth / width);
}

int PosToMapY(float y)
{
    return (y + (windowHeight / 2)) / (windowHeight / height);
}

float MapToPosX(int ind)
{
    return (windowWidth / width) * ind - (windowWidth / 2) + ((windowWidth / width) / 2);
}

float MapToPosY(int ind)
{
    return -((windowHeight / height) * ind - (windowHeight / 2) + ((windowHeight / height) / 2));
}

float GetSqDistance(float ax, float ay, float bx, float by)
{
    return ((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by));
}