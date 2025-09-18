#include "AudioResource.h"

AudioResource::~AudioResource()
{
	UnloadData();
}

void AudioResource::LoadData(const std::string& name)
{
	audio = AEAudioLoadMusic(name.c_str());
	data = &audio;
}

void AudioResource::UnloadData()
{
	AEAudioUnloadAudio(audio);
	data = nullptr;
}
