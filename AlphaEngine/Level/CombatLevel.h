// Author : sinu

#pragma once
#include "BaseLevel.h"

class GameObject;

namespace level
{
	class CombatLevel : public GSM::BaseLevel
	{
		GameObject* player = nullptr;
		GameObject* directionArrow = nullptr;
		GameObject* enemy = nullptr;

		int level;

	public:
		CombatLevel(int _level) : level(_level) {}

		void Init() override;
		void Update() override;
		void Exit() override;
	};
}