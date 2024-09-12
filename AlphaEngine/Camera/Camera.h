#pragma once
#include "AEEngine.h"

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

	float speed = 340;
	float height = 1;

	bool fix = true;

	AEMtx33 world_to_ndc_xform;

public:
	static Camera& GetInstance()
	{
		static Camera instance;
		return instance;
	}

	void Update();

	AEMtx33& GetMatrix() { return world_to_ndc_xform; }
	void GetPos(float* px, float* py) { *px = x; *py = y; }

	void AddHeight(float value);
	void SetHeight(float value);

	void SetPos(float _x, float _y);
};