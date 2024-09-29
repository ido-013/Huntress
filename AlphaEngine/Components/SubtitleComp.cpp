#include "SubtitleComp.h"
#include "AEEngine.h"

std::map<std::string, Subtitle> SubtitleComp::contexts;
std::vector<DissolveSubtitle> SubtitleComp::subtitles;
f64 SubtitleComp::currTime = 0;
s8 SubtitleComp::pFont = NULL;


SubtitleComp::SubtitleComp()
{
}

SubtitleComp::~SubtitleComp()
{
}

void SubtitleComp::InitFont(std::string ttfDirectory, int fontHeight)
{
	pFont = AEGfxCreateFont(ttfDirectory.c_str(), fontHeight);
}

void SubtitleComp::DestroyFont()
{
	if (pFont != NULL)
		AEGfxDestroyFont(pFont);
}

void SubtitleComp::OnSubtitle(Subtitle subtitle)
{
	AEGfxPrint(pFont, subtitle.content.c_str(), subtitle.loc.x, subtitle.loc.y, subtitle.size, subtitle.r, subtitle.g, subtitle.b, subtitle.a);
}

void SubtitleComp::AddSubtitle(Subtitle subtitle)
{
	contexts.emplace(subtitle.content, subtitle);
}

bool SubtitleComp::FindSubtitle(std::string str)
{
	if (contexts.find(str) != contexts.end())
		return true;
	return false;
}

void SubtitleComp::ModifySubtitle(std::string str1, std::string str2)
{
	if (contexts.find(str1) == contexts.end())
		return;
	contexts.find(str1)->second.content = str2;
}

void SubtitleComp::ModifySubtitle(std::string str1, bool Alpha)
{
	if (contexts.find(str1) == contexts.end())
		return;
	contexts.find(str1)->second.a = Alpha;
}


void SubtitleComp::RemoveSubtitle(std::string str)
{
	contexts.erase(str);
}

void SubtitleComp::ClearSubtitle()
{
	contexts.clear();
	subtitles.clear();
}

void SubtitleComp::IntersectDissolveText(DissolveSubtitle dissolveSubtitle)
{
	if (dissolveSubtitle.startIntersectTime + dissolveSubtitle.endIntersectTime > dissolveSubtitle.duration || 
		dissolveSubtitle.duration <= 0 || dissolveSubtitle.startIntersectTime < 0 || dissolveSubtitle.endIntersectTime < 0)
	{
		std::cout << "In \"SubtitleComp::IntersectDissolve(Subtitle subtitle, f64 duration, f64 startIntersectTime, f64 endIntersectTime)\" Value Error" << std::endl;
		return;
	}
	if (!subtitles.empty())
	{
		subtitles.clear();
		currTime = 0;
	}
	std::cout << "Add Text " << dissolveSubtitle.subtitle.content << std::endl;
	subtitles.push_back(dissolveSubtitle);
}

void SubtitleComp::Update()
{
	if (!subtitles.empty())
	{
		if (subtitles.front().duration >= currTime)
		{
			if (subtitles.front().startIntersectTime >= currTime)
			{
				subtitles.front().subtitle.a = (f32)currTime / (f32)subtitles.front().startIntersectTime;
			}
			if (subtitles.front().duration - subtitles.front().endIntersectTime <= currTime)
			{
				subtitles.front().subtitle.a = 1 - (((f32)currTime - (f32)(subtitles.front().duration - subtitles.front().endIntersectTime)) / (f32)subtitles.front().endIntersectTime);
			}
			OnSubtitle(subtitles.front().subtitle);
			currTime += AEFrameRateControllerGetFrameTime();
		}
		else
		{
			currTime = 0;
			subtitles.erase(subtitles.begin());
			std::cout << "Erase Text" << std::endl;
		}
	}
	if (!contexts.empty())
	{
		for (auto temp : contexts)
		{
			OnSubtitle(temp.second);
		}
	}
}

DissolveSubtitle::DissolveSubtitle(Subtitle subtitleV, f64 durationV, f64 startIntersectTimeV, f64 endIntersectTimeV) :
	subtitle(subtitleV), duration(durationV), startIntersectTime(startIntersectTimeV), endIntersectTime(endIntersectTimeV)
{
}

DissolveSubtitle::~DissolveSubtitle()
{
}

Subtitle::Subtitle(AEVec2 locV, float sizeV, std::string contentV, f32 rV, f32 gV, f32 bV, f32 aV) :
	loc(locV), size(sizeV), content(contentV), r(rV), g(gV), b(bV), a(aV)
{
}

Subtitle::~Subtitle()
{
}
