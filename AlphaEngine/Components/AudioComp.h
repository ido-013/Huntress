#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../ComponentManager/BaseComponent.h"
#include "AEAudio.h"

class AudioComp : public BaseComponent
{
private:
	AudioComp(const AudioComp& other) = delete;
	AudioComp& operator=(const AudioComp& other) = delete;

	AEAudioGroup group;
	
	std::map<std::string, AEAudio> audio;

	std::string current;

	float volume = 0.5f;
	float pitch = 1;

	int preFlag = 0;
	int flag = 0;

public:
	AudioComp(GameObject* owner);
	~AudioComp();

	void Update();

	void playAudio(s32 loops, std::string name);
	void playAudio(s32 loops, std::string name, float _volume);

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetAudio(std::string s);
	void UnloadAudio();

	static BaseRTTI* CreateAudioComponent(GameObject* owner);
	static constexpr const char* TypeName = "AudioComp";
};