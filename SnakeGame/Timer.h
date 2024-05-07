#pragma once
#include <functional>
#include <vector>
#include "Stopwatch.h"
#include "Event.h"

class Timer : public Stopwatch
{
public:
	Timer(float duration = 2.0f, bool bIsLooping = false);
	void Update();
	void SetDuration(float value) { _duration = value; }
	float GetRemainingSeconds() const;
	Event<> onTimerFired;

private:
	float _duration;
	bool _bIsLooping;
};