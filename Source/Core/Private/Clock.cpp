#include "Clock.h"
#include <Windows.h>

C3_NAMESPACE_BEGIN

FPerfTimer::FPerfTimer()
{
}

void FPerfTimer::Init()
{
	int64_t CounterFreq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&CounterFreq);
	SecondsPerCount = 1.0 / (double)CounterFreq;

	int64_t Count;
	QueryPerformanceCounter((LARGE_INTEGER*)&Count);
	CurrCount = Count;
	PrevCount = Count;
	CountDuringGame = 0;

	bPaused = false;
	bJustUnpaused = false;

	DeltaTime = 0.0;
}

void FPerfTimer::Tick()
{
	if (bPaused)
	{
		DeltaTime = 0.0;
	}
	else if(bJustUnpaused)
	{
		bJustUnpaused = false;
		QueryPerformanceCounter((LARGE_INTEGER*)&CurrCount);
		PrevCount = CurrCount;
		DeltaTime = 0.0;
	}
	else
	{
		PrevCount = CurrCount;
		QueryPerformanceCounter((LARGE_INTEGER*)&CurrCount);
		DeltaTime = (CurrCount - PrevCount) * SecondsPerCount;
		if (DeltaTime < 0.0)
			DeltaTime = 0.0;
		CountDuringGame += CurrCount - PrevCount;
	}
}

void FPerfTimer::SwitchPause()
{
	if(bPaused)
	{
		bPaused = false;
		bJustUnpaused = true;
	}
	else
	{
		bPaused = true;
	}
}

bool FPerfTimer::IsPaused()
{
	return bPaused;
}

float FPerfTimer::GetGameTime() const
{
	return static_cast<float>(CountDuringGame * SecondsPerCount);
}

float FPerfTimer::GetDeltaTime() const
{
	return static_cast<float>(DeltaTime);
}

C3_NAMESPACE_END
