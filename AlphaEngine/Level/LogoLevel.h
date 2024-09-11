#pragma once
#include "BaseLevel.h"

class GameObject;

namespace level
{
	class LogoLevel : public GSM::BaseLevel
	{
	private:
		GameObject* digipenLogo = nullptr;
		GameObject* teamLogo = nullptr;

		float timer = 0.f;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
