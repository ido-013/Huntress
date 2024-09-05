#pragma once
#include "BaseLevel.h"

class GameObject;

namespace level
{
	class ClearLevel : public GSM::BaseLevel
	{
		GameObject* Credit = nullptr;
	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
