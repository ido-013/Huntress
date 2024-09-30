#pragma once

#include "../ComponentManager/GraphicComponent.h"
#include <string>
#include <map>
#include "AEEngine.h"

class Subtitle
{
public:
	Subtitle(AEVec2 locV, float sizeV, std::string contentV, f32 rV, f32 gV, f32 bV, f32 aV);
	~Subtitle();

	AEVec2 loc;
	float size;
	std::string content;
	f32 r;
	f32 g;
	f32 b;
	f32 a;
};

class DissolveSubtitle	
{
public:
	DissolveSubtitle(Subtitle subtitleV, f64 durationV, f64 startIntersectTimeV, f64 endIntersectTimeV);
	~DissolveSubtitle();

	Subtitle subtitle;
	f64 duration;
	f64 startIntersectTime;
	f64 endIntersectTime;
};

class SubtitleComp
{
public:
	
	SubtitleComp();
	~SubtitleComp();
	
	static std::map<std::string, Subtitle> contexts;
	static std::vector<DissolveSubtitle> subtitles;
	static f64 currTime;
	static s8 pFont;

	static void InitFont(std::string ttfDirectory, int fontHeight);
	static void DestroyFont();
	
	static void OnSubtitle(Subtitle subtitle);
	static void AddSubtitle(Subtitle subtitle);
	static bool FindSubtitle(std::string str);
	static void ModifySubtitle(std::string str1, std::string str2);
	static void ModifySubtitle(std::string str1, bool Alpha);
	static void RemoveSubtitle(std::string str);
	static void ClearSubtitle();

	static void IntersectDissolveText(DissolveSubtitle dissolveSubtitle);

	static void Update();
};