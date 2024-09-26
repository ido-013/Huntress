#pragma once
#pragma once
#include "../UIM/BtnManager.h"
#include "../GameObject/GameObject.h"
#include"../UI/StoreUI.h"
#include <string>
class EscUI {
	GameObject* BgUI = nullptr;
	GameObject* RestartBtn = nullptr;
	GameObject* QuitBtn = nullptr;
	GameObject* CloseBtn = nullptr;

	bool isOpen = false;

public:
	bool getOpen();
	void SetUIVisibility(bool isVisible);
	void SetEscUI();
	void Setoff();
	void InitEscUI();
	void UpdateEscUI(StoreUI *);
	void ExitEscUI();
};