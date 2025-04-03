#pragma once
#include "BaseLevel.h"
#include "AEEngine.h"

class GameObject;

namespace level
{
	class LogoLevel : public GSM::BaseLevel
	{
	private:
		GameObject* digipenLogo = nullptr;
		GameObject* teamLogo = nullptr;

		f64 timer = 0;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
