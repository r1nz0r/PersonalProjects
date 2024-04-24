#include "Stopwatch.h"
#include <iostream>

Stopwatch::Stopwatch() :
    _startTime(GetCurrentSystemTime()),
    _accumulatedTime(duration::zero()),
    _bIsRunning(false)
{}

void Stopwatch::Start()
{
    if (!_bIsRunning)
    {
        _startTime = GetCurrentSystemTime(); // Обновляем стартовое время в соответствии с системным
        _bIsRunning = true;
    }
}

void Stopwatch::Pause()
{
    if (_bIsRunning)
    {
        _accumulatedTime += GetCurrentSystemTime() - _startTime; // Сохраняем текущее время паузы.
        _bIsRunning = false;
    }
}

void Stopwatch::Reset()
{
    _startTime = GetCurrentSystemTime();
    _accumulatedTime = duration::zero();
    _bIsRunning = false;
}

void Stopwatch::Restart()
{
    Reset();
    Start();
}

float Stopwatch::GetElapsedTimeSeconds() const
{
    if (!_bIsRunning) // Проверяем стоит ли таймер на паузе
        return std::chrono::duration_cast<duration>(_accumulatedTime).count(); // Возвращаем аккумулированное время
    
    auto seconds = std::chrono::duration_cast<duration>(_accumulatedTime + GetCurrentSystemTime() - _startTime).count();
    return seconds;
}
