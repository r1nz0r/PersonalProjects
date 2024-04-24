#include "Stopwatch.h"

Stopwatch::Stopwatch()
    : _clock(),
    _pauseTime(0.0f),
    _bIsRunning(true)
{}

void Stopwatch::Start()
{
    if (!_bIsRunning)
    {
        _clock.restart();
        _bIsRunning = true;
    }
}

void Stopwatch::Pause()
{
    if (_bIsRunning)
    {
        _pauseTime += _clock.getElapsedTime().asSeconds(); // Сохраняем текущее время паузы.
        _bIsRunning = false;
    }
}

void Stopwatch::Reset()
{
    _clock.restart();
    _pauseTime = 0.0f;
    _bIsRunning = false;
}

void Stopwatch::Restart()
{
    Reset();
    Start();
}

float Stopwatch::GetElapsedTime() const
{
    if (!_bIsRunning)
        return _pauseTime;    

    return _pauseTime + _clock.getElapsedTime().asSeconds();
}
