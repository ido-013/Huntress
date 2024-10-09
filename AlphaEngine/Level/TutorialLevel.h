#pragma once
#include "BaseLevel.h"
#include "AEEngine.h"

class GameObject;

namespace level
{
	class TutorialLevel : public GSM::BaseLevel
	{
	private:
		GameObject* img = nullptr;
		int ind = 1;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
