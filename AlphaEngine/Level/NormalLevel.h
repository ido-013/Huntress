#pragma once
#include "BaseLevel.h"
#include "../UI/StoreUI.h"

class GameObject;

namespace level
{
	class NormalLevel : public GSM::BaseLevel
	{
		GameObject* player = nullptr;
		GameObject* directionArrow = nullptr;
		GameObject* enemy = nullptr;
		StoreUI storeUI;

		int level;
	public:
		NormalLevel(int _level) : level(_level) {}

		void Init() override;
		void Update() override;
		void Exit() override;
	};
}