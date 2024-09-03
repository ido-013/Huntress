#pragma once
#include "../GameObject/GameObject.h"
class GameObject;
void InitCombatUI();
void UpdateCombatUI(GameObject* player, GameObject* enemy);
void ExitCombatUI();