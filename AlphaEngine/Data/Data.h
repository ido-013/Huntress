#pragma once

class Data
{
public:
	class PlayerData
	{
	public:
		PlayerData();
		int gold;
		float maxLife;
		float hp;
		float damage;
		float armor;
		// 아이템이나 업그레이드 상황 추가
		void InitData(int goldV, float maxLifeV, float hpV, float damageV, float armorV)
		{
			gold = goldV, maxLife = maxLifeV, hp = hpV, damage = damageV, armor = armorV;
		};
	};
	class EnemyData
	{
	public:
		EnemyData();
		float hp;
		float damage;
		float armor;
		enum GRADE {
			Normal = 0,
			Elite = 1,
			Boss = 2
		}grade;
		void InitData(float hpV, float damageV, float armorV, GRADE gradeV)
		{
			hp = hpV, damage = damageV, armor = armorV, grade = gradeV;
		};
	};
	class CombatData
	{
	public:
		CombatData();
		int randomValue;
		float windAngle;
		float windPower;
		float angle;
		float power;
		int moveGauge;
		void InitData(int randomValueV, float windAngleV, float windPowerV, float angleV, float powerV, int moveGaugeV)
		{
			randomValue = randomValueV, windAngle = windAngleV, windPower = windPowerV, angle = angleV, power = powerV, moveGauge = moveGaugeV;
		};
	};

	static void PrintPlayerData(Data::PlayerData data);
	static void PrintEnemyData(Data::EnemyData data);
	static void PrintCombatData(Data::CombatData data);
	static void PrintSeparator();
};