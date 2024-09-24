#pragma once
#include "../UIM/BtnManager.h"
#include "../GameObject/GameObject.h"
#include <string>
class ControllUI {
	GameObject* BgUI = nullptr;
	GameObject* ControlUI = nullptr;
	GameObject* CloseBtn = nullptr;
	GameObject* controlFrame = nullptr;
	bool isOpen = true;

public:
	void SetUIVisibility(bool isVisible);
	void SetControllUI();
	void Setoff();
	void InitControllUI();
	void UpdateControllUI();
	void ExitControllUI();
};