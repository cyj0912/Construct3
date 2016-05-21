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
	float GetTotalTime() const;
    float GetDeltaTime() const;

private:
	bool bPaused;
	bool bJustUnpaused;

	double DeltaTime;
	std::uint64_t CurrCount;
	std::uint64_t PrevCount;
	std::uint64_t CountDuringGame;
};

template <typename T>
class FTimer
{
    const T& ParentTimer;
    bool bPaused;
    bool bJustUnpaused;
    float DeltaTime;
    float CurrTime;
    float PrevTime;
    float TotalTime;
public:
    FTimer(const T& parent) : ParentTimer(parent)
    {
    }

    void Init()
    {
        bPaused = false;
        bJustUnpaused = false;
        DeltaTime = CurrTime = PrevTime = TotalTime = 0.0f;
    }

    void Tick()
    {
        if (bPaused)
        {
            DeltaTime = 0.0f;
        }
        else if(bJustUnpaused)
        {
            bJustUnpaused = false;
            CurrTime = ParentTimer.GetTotalTime();
            PrevTime = CurrTime;
            DeltaTime = 0.0f;
        }
        else
        {
            PrevTime = CurrTime;
            CurrTime = ParentTimer.GetTotalTime();
            DeltaTime = CurrTime - PrevTime;
            if (DeltaTime < 0.0f)
                DeltaTime = 0.0f;
            TotalTime += DeltaTime;
        }
    }

    void SwitchPause()
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

    bool IsPaused()
    {
        return bPaused;
    }

    float GetTotalTime() const
    {
        return TotalTime;
    }

    float GetDeltaTime() const
    {
        return DeltaTime;
    }
};
C3_NAMESPACE_END
