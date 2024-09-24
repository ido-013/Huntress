#pragma once
#include "../UIM/BtnManager.h"
#include <string>
class ButtonComp;
class PlayerComp;
class AudioComp;
class TransformComp;
class SpriteComp;
class GameObject;
class StoreUI {
	GameObject* Frame[6] = { nullptr };
	GameObject* Openbtn = nullptr;
	GameObject* StorePopup = nullptr;
	GameObject* Closebtn = nullptr;
	GameObject* smallPotion = nullptr;
	GameObject* UpHp = nullptr;
	GameObject* bigPotion = nullptr;
	GameObject* UpAttack = nullptr;
	GameObject* UpDefense = nullptr;
	GameObject* Arrow = nullptr;
	GameObject* Cost[6] = { nullptr };
	bool isStore = true;

public:

	static std::string goldText;
	void SetUIVisibility(bool isVisible);
	void SetStoreUI();
	void Setoff();
	void InitStoreUI(GameObject* player);
	void UpdateStoreUI();
	void ExitStoreUI();
};