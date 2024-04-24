#pragma once
#include <chrono>

class Stopwatch
{
    using timePoint = std::chrono::steady_clock::time_point;
    using duration = std::chrono::duration<float>;

public:
    explicit Stopwatch();

    void Start();
    void Pause();
    void Reset();
    void Restart();
    bool IsRunning() const { return _bIsRunning; }
    float GetElapsedTimeSeconds() const; // Возвращает время в секундах

private:   
    timePoint _startTime;
    duration _accumulatedTime;
    timePoint GetCurrentSystemTime() const { return std::chrono::steady_clock::now(); }
    bool _bIsRunning;
};