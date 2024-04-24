#include "Timer.h"

Timer::Timer(float duration, bool bIsLooping) :
	Stopwatch(),
	_duration(duration),
	_bIsLooping(bIsLooping),
	_callBacks()
{}

void Timer::Subscribe(std::function<void()> callback)
{
	_callBacks.push_back(callback);
}

void Timer::Update()
{
	float elapsedSeconds = GetElapsedTimeSeconds();

	if (IsRunning() && elapsedSeconds >= _duration)
	{
		OnTimerFired();
		Reset();

		if (_bIsLooping)
			Start();
	}
}

float Timer::GetRemainingSeconds() const
{
	return _duration - GetElapsedTimeSeconds();
}

void Timer::OnTimerFired()
{
	for (const auto& callback : _callBacks)
	{
		callback();
	}
}
