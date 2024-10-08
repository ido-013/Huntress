#pragma once
#include "AEEngine.h"
#include "../Combat/Combat.h"

class Camera
{
private:
	Camera();

	Camera(const Camera& other) = delete;
	const Camera& operator=(const Camera& other) = delete;
	~Camera();

	static Camera* ptr;

	float srcX = 0;
	float srcY = 0;

	float x = 0;
	float y = 0;

	float speed = 400;
	float height = 2;

	CombatComp::STATE preState;

	AEMtx33 world_to_ndc_xform[2];

public:
	bool fix = true;

	static Camera& GetInstance()
	{
		static Camera instance;
		return instance;
	}

	float minX = 0;
	float maxX = 2500;

	float minY = -1865;
	float maxY = -800;

	void Update();

	AEMtx33& GetMatrix() { return world_to_ndc_xform[0]; }
	AEMtx33& GetMatrix2() { return world_to_ndc_xform[1]; }
	void GetPos(float* px, float* py);

	void AddHeight(float value);
	void SetHeight(float value);

	void SetPos(float _x, float _y);
};