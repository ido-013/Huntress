#include "Camera.h"
#include "../Combat/Combat.h"
#include "../Combat/Projectile.h"

Camera::Camera() : world_to_ndc_xform(), preTurn(CombatComp::turn)
{
}

Camera::~Camera()
{

}

void Camera::Update()
{
	AEMtx33Identity(&world_to_ndc_xform);

	if (CombatComp::state == CombatComp::COMBAT 
		&& !Projectile::isLaunchProjectile)
	{
		f64 dt = AEFrameRateControllerGetFrameTime();

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

			if (mouseX > AEGfxGetWindowWidth())
			{
				x += speed * dt;
			}

			else if (mouseX < 0)
			{
				x -= speed * dt;
			}

			if (mouseY > AEGfxGetWindowHeight())
			{
				y -= speed * dt;
			}

			else if (mouseY < 0)
			{
				y += speed * dt;
			}

			//Press Space
			if (AEInputCheckTriggered(AEVK_SPACE) || preTurn != CombatComp::turn)
			{
				x = srcX;
				y = srcY;
			}

			AEMtx33TransApply(&world_to_ndc_xform, &world_to_ndc_xform, -x, -y);
		}
	}
	else
		AEMtx33TransApply(&world_to_ndc_xform, &world_to_ndc_xform, -srcX, -srcY);

	AEMtx33ScaleApply(&world_to_ndc_xform, &world_to_ndc_xform, 1 / height, 1 / height);

	preTurn = CombatComp::turn;
}

void Camera::AddHeight(float value)
{
	if (CombatComp::state == CombatComp::COMBAT)
	{
		height += value;
		height = AEClamp(height, 0.5, 10);
	}
}

void Camera::SetHeight(float value)
{
	height = AEClamp(value, 0.5, 10);
}

void Camera::SetPos(float _x, float _y)
{
	srcX = _x;
	srcY = _y;
}

