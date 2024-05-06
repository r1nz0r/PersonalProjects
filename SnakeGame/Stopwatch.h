#pragma once
#include <chrono>

class Stopwatch
{
    using timePoint = std::chrono::high_resolution_clock::time_point;
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
    timePoint GetCurrentSystemTime() const { return std::chrono::high_resolution_clock::now(); }
    bool _bIsRunning;
};