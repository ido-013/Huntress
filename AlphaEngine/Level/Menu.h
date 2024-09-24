#pragma once
#include "BaseLevel.h"

class GameObject;

namespace level
{
	class Menu : public GSM::BaseLevel
	{
		GameObject* menuBg = nullptr;
		GameObject* Logo = nullptr;
		GameObject* startButtonObj = nullptr;
		GameObject* ControllButtonObj = nullptr;
		GameObject* quitButtonObj = nullptr;
	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
