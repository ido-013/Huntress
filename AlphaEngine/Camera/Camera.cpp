#include "Camera.h"
#include "../Combat/Combat.h"
#include "../Combat/Projectile.h"
#include "../GameObjectManager/GameObjectManager.h"

#define PADDING 20

Camera::Camera() : world_to_ndc_xform()
{
}

Camera::~Camera()
{

}

void Camera::Update()
{
	AEMtx33Identity(&world_to_ndc_xform[0]);
	AEMtx33Identity(&world_to_ndc_xform[1]);

	if (CombatComp::state == CombatComp::COMBAT)
	{
		float dt = (float)AEFrameRateControllerGetFrameTime();

		if (AEInputCheckTriggered(AEVK_Y))
		{
			fix = !fix;
		}

		if (fix)
		{
			x = srcX;
			y = srcY;
			AEMtx33TransApply(&world_to_ndc_xform[0], &world_to_ndc_xform[0], -srcX, -srcY);
			AEMtx33TransApply(&world_to_ndc_xform[1], &world_to_ndc_xform[1], -srcX, -srcY);
		}

		else
		{
			//Camera movement
			int mouseX, mouseY;
			AEInputGetCursorPosition(&mouseX, &mouseY);

			if (mouseX > AEGfxGetWindowWidth() - PADDING)
			{
				x += speed * dt;
			}

			else if (mouseX < PADDING)
			{
				x -= speed * dt;
			}

			if (mouseY > AEGfxGetWindowHeight() - PADDING)
			{
				y -= speed * dt;
			}

			else if (mouseY < PADDING)
			{
				y += speed * dt;
			}

			x = AEClamp(x, minX, maxX);
			y = AEClamp(y, minY, maxY);

			//Press Space
			if (AEInputCheckTriggered(AEVK_SPACE))
			{
				AEVec2 playerPos = GameObjectManager::GetInstance().GetObj("player")->GetComponent<TransformComp>()->GetPos();
				x = playerPos.x;
				y = playerPos.y;
			}

			AEMtx33TransApply(&world_to_ndc_xform[0], &world_to_ndc_xform[0], -x, -y);
			AEMtx33TransApply(&world_to_ndc_xform[1], &world_to_ndc_xform[1], -x, -y);
		}
	}
	else
	{
		AEMtx33TransApply(&world_to_ndc_xform[0], &world_to_ndc_xform[0], -srcX, -srcY);
		AEMtx33TransApply(&world_to_ndc_xform[1], &world_to_ndc_xform[1], -srcX, -srcY);
	}

	AEMtx33ScaleApply(&world_to_ndc_xform[0], &world_to_ndc_xform[0], 2 / height, 2 / height);
	AEMtx33ScaleApply(&world_to_ndc_xform[1], &world_to_ndc_xform[1], 0.1 / height, 0.1 / height);
}

void Camera::GetPos(float* px, float* py)
{
	if (fix)
	{
		*px = srcX;
		*py = srcY;
	}
	else
	{
		*px = x;
		*py = y;
	}
}

void Camera::AddHeight(float value)
{
	if (CombatComp::state == CombatComp::COMBAT)
	{
		height += value;
		height = AEClamp(height, 0.5, 4);
	}
}

void Camera::SetHeight(float value)
{
	height = AEClamp(value, 0.5, 4);
}

void Camera::SetPos(float _x, float _y)
{
	srcX = _x;
	srcY = _y;

	srcX = AEClamp(srcX, minX, maxX);
	srcY = AEClamp(srcY, minY, maxY);
}

