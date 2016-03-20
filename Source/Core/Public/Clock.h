#pragma once
#include "Core.h"
#include <cstdint>
C3_NAMESPACE_BEGIN
class FPerfTimer
{
public:
	FPerfTimer();

	void Init();
	void Tick();
	void SwitchPause();
	bool IsPaused();

	float GetGameTime() const;
	float GetDeltaTime() const;

private:
	double SecondsPerCount;

	bool bPaused;
	bool bJustUnpaused;

	double DeltaTime;
	std::int64_t CurrCount;
	std::int64_t PrevCount;
	std::int64_t CountDuringGame;
};
C3_NAMESPACE_END
