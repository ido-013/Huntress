#pragma once
#include "../GameObject/GameObject.h"
class GameObject;
void InitCombatUI(GameObject* player, GameObject* enemy, GameObject* directionArrow);
void UpdateCombatUI(GameObject* player, GameObject* enemy, GameObject* directionArrow);
void ExitCombatUI();