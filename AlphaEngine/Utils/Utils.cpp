#include "Utils.h"
#include "AEEngine.h"

float GetMouseCursorPositionX()
{
    s32 x, y;
    AEInputGetCursorPosition(&x, &y);
    x -= windowWidthHalf;
    return (float)x;
}

float GetMouseCursorPositionY()
{
    s32 x, y;
    AEInputGetCursorPosition(&x, &y);
    y -= windowHeightHalf;
    y = -y;
    return (float)y;
}

int PosToMapX(float x)
{
    return (int)(x + (windowWidth / 2)) / (windowWidth / width);
}

int PosToMapY(float y)
{
    return (int)(y + (windowHeight / 2)) / (windowHeight / height);
}

float MapToPosX(float ind)
{
    //return (windowWidth / width) * ind - (windowWidth / 2) + ((windowWidth / width) / 2);
    return ind * width;
}

float MapToPosY(float ind)
{
    //return -((windowHeight / height) * ind - (windowHeight / 2) + ((windowHeight / height) / 2));
    return -ind * height;
}

float GetSqDistance(float ax, float ay, float bx, float by)
{
    return ((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by));
}