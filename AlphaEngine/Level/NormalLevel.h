#pragma once
#include "BaseLevel.h"

class GameObject;
class StoreUI;

namespace level
{
	class NormalLevel : public GSM::BaseLevel
	{
		GameObject* player = nullptr;
		GameObject* directionArrow = nullptr;
		GameObject* enemy = nullptr;

		int level;
	public:
		NormalLevel(int _level) : level(_level) {}

		void Init() override;
		void Update() override;
		void Exit() override;
	};
}