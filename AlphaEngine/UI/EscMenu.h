#pragma once
#pragma once
#include "../UIM/BtnManager.h"
#include "../GameObject/GameObject.h"
#include <string>
class EscUI {
	GameObject* BgUI = nullptr;
	GameObject* RestartBtn = nullptr;
	GameObject* QuitBtn = nullptr;
	GameObject* CloseBtn = nullptr;

	bool isOpen = true;

public:
	void SetUIVisibility(bool isVisible);
	void SetControllUI();
	void Setoff();
	void Setmenu();
	void InitEscUI();
	void UpdateEscUI();
	void ExitEscUI();
};