#pragma once

#include "../ComponentManager/LogicComponent.h"

class Data : public LogicComponent
{
public:
	class PlayerData
	{
	public:
		float hp;
		float damage;
		float armor;
		// 아이템이나 업그레이드 상황 추가
	};
	class EnemyData
	{
	public:
		float hp;
		float damage;
		float armor;
		enum GRADE {
			Normal,
			Elite,
			Boss
		}grade;
	};
	class CombatData
	{
	public:
		int randomValue;
		float windAngle;
		float windPower;
		float angle;
		float power;
		float moveGauge;
	};
};