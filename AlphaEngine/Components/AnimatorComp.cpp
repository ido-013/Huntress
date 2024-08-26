#include "AnimatorComp.h"
#include "../Components/SpriteComp.h"

AnimatorComp::AnimatorComp(GameObject* _owner) : GraphicComponent(_owner), loop(false), speed(1.f), 
												 current(nullptr), timer(0), ind(0)
{

}

AnimatorComp::~AnimatorComp()
{
	for (auto& it : animation)
	{
		delete it.second;
	}
}

void AnimatorComp::AddAnimation(std::string _name)
{
	animation.insert({ _name, new Animation });
}

void AnimatorComp::UpdateAnimation(double _time, std::string _spriteName, std::string _name)
{
	auto it = animation.find(_name);
	
	if (it != animation.end())
	{
		it->second->AddFrame(_time, _spriteName);
	}
}

void AnimatorComp::SetAnimation(bool _loop, double _speed, std::string _name)
{
	loop = _loop;
	speed = _speed;
	timer = 0;
	
	auto it = animation.find(_name);
	if (it != animation.end())
	{
		current = it->second;
	}
}

void AnimatorComp::Update()
{
	SpriteComp* s = owner->GetComponent<SpriteComp>();

	if (!s)
		return;

	if (current != nullptr)
	{
		if (current->frame.empty())
			return;

		if (timer == 0)
		{
			s->SetTexture(current->frame[ind].second);
		}

		timer += AEFrameRateControllerGetFrameTime() * speed;

		if (timer > current->frame[ind].first)
		{
			timer = 0;
			ind++;

			if (ind >= current->size)
				ind = 0;

			s->SetTexture(current->frame[ind].second);

			if (!loop)
				current = nullptr;
		}
	}
}

void AnimatorComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("animation");

		if (it == compData->end())
			return;

		for (auto& aniIt : *it)
		{
			std::string name = aniIt.find("name").value();
			AddAnimation(name);
			
			for (auto& frameIt : *aniIt.find("frame"))
			{
				UpdateAnimation(frameIt[0], frameIt[1], name);
			}
		}
	}
}

json AnimatorComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;

	json aniData;
	for (auto& it : animation)
	{
		aniData["name"] = it.first;

		for (auto& aniIt : it.second->frame)
		{
			aniData["frame"].push_back({aniIt.first, aniIt.second});
		}

		compData["animation"].push_back(aniData);
	}
	
	
	data["compData"] = compData;

	return data;
}

BaseRTTI* AnimatorComp::CreateAnimatorComponent(GameObject* owner)
{
	BaseRTTI* p = new AnimatorComp(owner);
	owner->AddComponent<AnimatorComp>(static_cast<AnimatorComp*>(p));
	return p;
}

