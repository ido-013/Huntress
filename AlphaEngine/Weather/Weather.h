#pragma once
#include "../GameObject/GameObject.h"
#include "AEVec2.h"

constexpr int size = 200;

class Weather
{
private:
	Weather() = default;
	Weather(const Weather& other) = delete;
	const Weather& operator=(const Weather& other) = delete;
	~Weather() = default;

	GameObject* go[size] = { nullptr };
	AEVec2 minPos = { 0, 0 };
	AEVec2 maxPos = { 0, 0 };
	
	AEVec2 scale = { 1, 1 };
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	float a = 0;

	int index = 0;	

	AEVec2 preWindVec = { 0, -150 };
	float maxTimer = 0.3f;

public:
	static Weather& GetInstance()
	{
		static Weather instance;
		return instance;
	}

	void ChangeWeather(AEVec2 _minPos, AEVec2 _maxPos, AEVec2 _scale, unsigned char _r, unsigned char _g, unsigned char _b, float _a, float _maxTimer);
	void Update();
	void ChangeWind(AEVec2 windVec);
	void ClearWeather();
};