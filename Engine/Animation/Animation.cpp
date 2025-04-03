#include "Animation.h"
#include "../ResourceManager/ResourceManager.h"

void Animation::AddFrame(const double& time, const std::string& spriteName)
{
	totalTime += time;
	size++;
	frame.push_back({ time, spriteName });
}
