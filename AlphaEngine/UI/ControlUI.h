#pragma once
#include "../UIM/BtnManager.h"
#include "../GameObject/GameObject.h"
#include <string>
class ControlUI {
	GameObject* BgUI = nullptr;
	GameObject* CtlUI = nullptr;
	GameObject* CloseBtn = nullptr;
	GameObject* controlFrame = nullptr;
	bool isOpen = true;

public:
	void SetUIVisibility(bool isVisible);
	void SetControlUI();
	void Setoff();
	void Setmenu();
	void InitControlUI();
	void UpdateControlUI();
	void ExitControlUI();
};