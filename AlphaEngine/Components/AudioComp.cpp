#include "AudioComp.h"
#include "AEEngine.h"
#include "AEAudio.h"
#include "../ComponentManager/ComponentManager.h"
#include "../ResourceManager/ResourceManager.h"

AudioComp::AudioComp(GameObject* owner) : BaseComponent(owner), group()
{
	ComponentManager<AudioComp>::GetInstance().AddComp(this);
	group = AEAudioCreateGroup();
}

AudioComp::~AudioComp()  
{	
	for (auto& it : audio)
	{
		ResourceManager::GetInstance().UnloadResource(it.first);
	}
	
	AEAudioStopGroup(group);
	AEAudioUnloadAudioGroup(group);
	ComponentManager<AudioComp>::GetInstance().DelComp(this);
}

void AudioComp::Update()
{

}

void AudioComp::playAudio(s32 loops, std::string name)
{
	auto it = audio.find(name);
	if (it != audio.end())
		AEAudioPlay(it->second, group, volume, pitch, loops);
}

void AudioComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("audio");
		for (auto& audioIt : *it)
		{
			SetAudio(audioIt);
		}

		it = compData->find("volume");
		volume = it.value();

		it = compData->find("pitch");
		pitch = it.value();
	}
}

json AudioComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;

	json audioList;
	for (auto& it : audio)
	{
		audioList.push_back(it.first);
	}

	compData["audio"] = audioList;
	compData["volume"] = volume;
	compData["pitch"] = pitch;
	data["compData"] = compData;

	return data;
}

void AudioComp::SetAudio(std::string name)
{
	audio.insert({ name, *ResourceManager::GetInstance().GetResource<AEAudio>(name) });
}

void AudioComp::UnloadAudio()
{
}

BaseRTTI* AudioComp::CreateAudioComponent(GameObject* owner)
{
	BaseRTTI* p = new AudioComp(owner);

	owner->AddComponent<AudioComp>(static_cast<BaseComponent*>(p));

	return p;
}

