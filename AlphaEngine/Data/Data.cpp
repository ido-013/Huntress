#include "Data.h"
#include <iostream>

void Data::PrintPlayerData(Data::PlayerData data)
{
	std::cout << "Player HP : " << data.hp << std::endl;
	std::cout << "Player Damage : " << data.damage << std::endl;
	std::cout << "Player Armor : " << data.armor << std::endl;
	PrintSeparator();
}

void Data::PrintEnemyData(Data::EnemyData data)
{
	std::cout << "Enemy HP : " << data.hp << std::endl;
	std::cout << "Enemy Damage : " << data.damage << std::endl;
	std::cout << "Enemy Armor : " << data.armor << std::endl;
	std::cout << "Enemy Grade : " << (data.grade == Data::EnemyData::GRADE::Normal ? "Normal" : data.grade == Data::EnemyData::GRADE::Elite ? "Elite" : "Boss") << std::endl;
	PrintSeparator();
}

void Data::PrintCombatData(Data::CombatData data)
{
	std::cout << "Combat randomValue : " << data.randomValue << std::endl;
	std::cout << "Combat windAngle : " << data.windAngle << std::endl;
	std::cout << "Combat windPower : " << data.windPower << std::endl;
	std::cout << "Combat angle : " << data.angle << std::endl;
	std::cout << "Combat power : " << data.power << std::endl;
	std::cout << "Combat moveGauge : " << data.moveGauge << std::endl;
	PrintSeparator();
}

void Data::PrintSeparator()
{
	std::cout << "---------------------------" << std::endl;
}

