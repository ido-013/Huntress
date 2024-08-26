#pragma once
#include <map>
#include <string>
#include "../ComponentManager/GraphicComponent.h"
#include "../Animation/Animation.h"

class AnimatorComp : public GraphicComponent
{
private:
	int ind;
	bool loop;
	double speed;
	double timer;
	std::map<std::string, Animation*> animation;
	Animation* current;

public:
	AnimatorComp(GameObject* _owner);
	~AnimatorComp();

	void AddAnimation(std::string _name);
	void UpdateAnimation(double _time, std::string _spriteName, std::string _name);

	void SetAnimation(bool _loop, double _speed, std::string _name);
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateAnimatorComponent(GameObject* owner);
	static constexpr const char* TypeName = "AnimatorComp";
};