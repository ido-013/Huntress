#pragma once
#include "BaseLevel.h"
#include "../UI/EscMenu.h"
class GameObject;

namespace level
{
	class ClearLevel : public GSM::BaseLevel
	{
		GameObject* Credit = nullptr;
		EscUI Escmenu;
	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
