#pragma once
#include "../GameObject/GameObject.h"

class CombatUI
{
	GameObject* UIBAR = nullptr;
	GameObject* PowerFrame = nullptr;
	GameObject* Power = nullptr;
	GameObject* MoveFrame = nullptr;
	GameObject* Move = nullptr;
	GameObject* Angle = nullptr;
	GameObject* playerAngle = nullptr;
	GameObject* DirectAngle = nullptr;
	GameObject* FrameUiBar = nullptr;
	GameObject* HPFrame = nullptr;
	GameObject* HP = nullptr;
	GameObject* enemyHPFrame = nullptr;
	GameObject* enemyHP = nullptr;
	GameObject* item[4] = { nullptr };
	GameObject* itemIcon[4] = { nullptr };
	GameObject* WindDirection = nullptr;
	GameObject* PreDirection = nullptr;
	GameObject* Wind = nullptr;
	GameObject* WindFrame = nullptr;
public:
	void InitCombatUI();
	void UpdateCombatUI();
	void ExitCombatUI();
	void Seton();
	void Setoff();


};

