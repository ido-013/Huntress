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
	AEMtx33Identity(&world_to_ndc_xform);

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
			AEMtx33TransApply(&world_to_ndc_xform, &world_to_ndc_xform, -srcX, -srcY);
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

			x = AEClamp(x, 0, 2500);
			y = AEClamp(y, -1865, 0);

			//Press Space
			if (AEInputCheckTriggered(AEVK_SPACE))
			{
				AEVec2 playerPos = GameObjectManager::GetInstance().GetObj("player")->GetComponent<TransformComp>()->GetPos();
				x = playerPos.x;
				y = playerPos.y;
			}

			AEMtx33TransApply(&world_to_ndc_xform, &world_to_ndc_xform, -x, -y);
		}
	}
	else
		AEMtx33TransApply(&world_to_ndc_xform, &world_to_ndc_xform, -srcX, -srcY);

	AEMtx33ScaleApply(&world_to_ndc_xform, &world_to_ndc_xform, 2 / height, 2 / height);
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

	srcX = AEClamp(srcX, 0, 2500);
	srcY = AEClamp(srcY, -1865, 0);
}

