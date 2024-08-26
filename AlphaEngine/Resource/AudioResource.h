#pragma once
#include "AEEngine.h"
#include "Resource.h"

class AudioResource : public Resource
{
private:
	AEAudio audio;

public:
	~AudioResource();
	void LoadData(const std::string& filename) override;
	void UnloadData() override;
};