#pragma once
#include <vector>
#include <string>
#include "AEEngine.h"

struct Animation
{
	std::vector<std::pair<double, std::string>> frame;
	double totalTime = 0;
	int size = 0;

	void AddFrame(const double&, const std::string&);
};
