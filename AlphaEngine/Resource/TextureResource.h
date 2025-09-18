#pragma once
#include "AEEngine.h"
#include "Resource.h"

class TextureResource : public Resource
{
public:
	~TextureResource();
	void LoadData(const std::string& filename) override;
	void UnloadData() override;
};