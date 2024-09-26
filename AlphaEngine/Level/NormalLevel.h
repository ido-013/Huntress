#pragma once
#include "BaseLevel.h"
#include "../UI/StoreUI.h"
#include "../UI/EscMenu.h"
class GameObject;

namespace level
{
	class NormalLevel : public GSM::BaseLevel
	{
		GameObject* player = nullptr;
		GameObject* directionArrow = nullptr;
		GameObject* enemy = nullptr;
		StoreUI storeUI;
		EscUI Escmenu;
		int level;
	public:
		NormalLevel(int _level) : level(_level) {}
		~NormalLevel() override;
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}