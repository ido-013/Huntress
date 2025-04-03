#pragma once
#include <vector>
#include <map>
#include <string>
#include <AEEngine.h>
class GameObject;

class ItemInfo
{
	bool isVisible = false;
public:
	~ItemInfo();

	void CreateItemInfo(const std::string& name, const std::string& texturePath);
	void SetonInfo(const std::string& name);
	void SetoffInfo(const std::string& name);
	void SetPosition(const std::string& name, const AEVec2& newPosition);
};