#include "Timer.h"

Timer::Timer(float duration, bool bIsLooping) :
	Stopwatch(),
	_duration(duration),
	_bIsLooping(bIsLooping),
	onTimerFired()
{}

void Timer::Update()
{
	float elapsedSeconds = GetElapsedTimeSeconds();

	if (IsRunning() && elapsedSeconds >= _duration)
	{
		onTimerFired.Notify();
		Reset();

		if (_bIsLooping)
			Start();
	}
}

float Timer::GetRemainingSeconds() const
{
	float remainingSeconds = _duration - GetElapsedTimeSeconds();
	return remainingSeconds > 0.0f ? remainingSeconds : 0.0f;
}
