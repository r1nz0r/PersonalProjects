#pragma once
#include <functional>
#include <vector>
#include "Stopwatch.h"

class Timer : public Stopwatch
{
public:
	Timer(float duration = 2.0f, bool bIsLooping = false);
	void Subscribe(std::function<void()> callback);
	void Update();
	void SetDuration(float value) { _duration = value; }
	float GetRemainingSeconds() const;

private:
	float _duration;
	bool _bIsLooping;
	std::vector<std::function<void()>> _callBacks;
	void OnTimerFired();
};

