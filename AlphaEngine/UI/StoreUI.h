#pragma once
#include "../UIM/BtnManager.h"
class ButtonComp;
class PlayerComp;
class AudioComp;
class TransformComp;
class SpriteComp;
class GameObject;
class StoreUI {
	GameObject* Openbtn = nullptr;
	GameObject* StorePopup = nullptr;
	GameObject* Closebtn = nullptr;
	GameObject* smallPotion = nullptr;
	GameObject* UpHp = nullptr;
	GameObject* fullPotion = nullptr;
	GameObject* UpAttack = nullptr;
	GameObject* UpDefense = nullptr;
	GameObject* Arrow = nullptr;

	bool isStore = false;
public:
	void SetUIVisibility(bool isVisible);
	void SetStoreUI();
	void Setoff();
	void InitStoreUI(GameObject* player);
	void UpdateStoreUI();
	void ExitStoreUI();
};