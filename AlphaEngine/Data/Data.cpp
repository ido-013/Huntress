#include "Data.h"
#include <iostream>
#include "AEEngine.h"

void Data::PrintPlayerData(Data::PlayerData data)
{
	std::cout << "Player GOLD : " << data.gold << std::endl;
	std::cout << "Player MAX HP : " << data.maxLife << std::endl;
	std::cout << "Player HP : " << data.hp << std::endl;
	std::cout << "Player Damage : " << data.damage << std::endl;
	std::cout << "Player Armor : " << data.armor << std::endl;
	PrintSeparator();
}

void Data::PrintEnemyData(Data::EnemyData data)
{
	std::cout << "Enemy MAX HP : " << data.maxLife << std::endl;
	std::cout << "Enemy HP : " << data.hp << std::endl;
	std::cout << "Enemy Damage : " << data.damage << std::endl;
	std::cout << "Enemy Armor : " << data.armor << std::endl;
	std::cout << "Enemy Grade : " << (data.grade == Data::EnemyData::GRADE::Normal ? "Normal" : data.grade == Data::EnemyData::GRADE::Elite ? "Elite" : "Boss") << std::endl;
	PrintSeparator();
}

void Data::PrintCombatData(Data::CombatData data)
{
	std::cout << "Combat randomValue : " << data.randomValue << std::endl;
	std::cout << "Combat windAngle : " << AERadToDeg(data.windAngle) << std::endl;
	std::cout << "Combat windPower : " << data.windPower << std::endl;
	std::cout << "Combat angle : " << AERadToDeg(data.angle) << std::endl;
	std::cout << "Combat power : " << data.power << std::endl;
	std::cout << "Combat moveGauge : " << data.moveGauge << std::endl;
	PrintSeparator();
}

void Data::PrintSeparator()
{
	std::cout << "---------------------------" << std::endl;
}
Data::PlayerData::PlayerData() : gold(0), maxLife(0), hp(0), damage(0), armor(0)
{
}

Data::EnemyData::EnemyData() : maxLife(0), hp(0), damage(0), armor(0), grade(Data::EnemyData::GRADE::Normal)
{
}

Data::CombatData::CombatData() : randomValue(0), windAngle(0), windPower(0), angle(0), power(0), moveGauge(0)
{
}


