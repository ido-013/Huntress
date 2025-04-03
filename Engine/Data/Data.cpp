#include "Data.h"
#include <iostream>
#include "AEEngine.h"

int Data::PlayerData::gold = 100;
float Data::PlayerData::maxLife = 50;
float Data::PlayerData::hp = 50;
float Data::PlayerData::damage = 5;
float Data::PlayerData::armor = 1;
Inventory Data::PlayerData::inventory = { false, {} };

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
	std::cout << "Combat randomValue1 : " << data.randomValue1 << std::endl;
	std::cout << "Combat randomValue2 : " << data.randomValue2 << std::endl;
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
Data::EnemyData::EnemyData() : maxLife(0), hp(0), damage(0), armor(0), grade(Data::EnemyData::GRADE::Normal)
{
}

void Data::EnemyData::LoadFromJson(const json& data)
{
	auto it = data.find("maxLife");
	maxLife = it.value();

	it = data.find("hp");
	hp = it.value();

	it = data.find("damage");
	damage = it.value();

	it = data.find("armor");
	armor = it.value();

	it = data.find("grade");
	grade = it.value();
}

json Data::EnemyData::SaveToJson()
{
	json data;

	data["maxLife"] = maxLife;
	data["hp"] = hp;
	data["damage"] = damage;
	data["armor"] = armor;
	data["grade"] = grade;

	return data;
}

Data::CombatData::CombatData() : randomValue1(0), randomValue2(0), windAngle(0), windPower(0), angle(0), power(0), moveGauge(0)
{
}


