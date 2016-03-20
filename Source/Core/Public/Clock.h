#pragma once
#include "Platform.h"
#include "Namespace.h"
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
	bool bPaused;
	bool bJustUnpaused;

	double DeltaTime;
	std::uint64_t CurrCount;
	std::uint64_t PrevCount;
	std::uint64_t CountDuringGame;
};
C3_NAMESPACE_END
