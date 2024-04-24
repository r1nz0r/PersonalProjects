#include "Timer.h"

Timer::Timer()
    : _clock(),
    _pauseTime(0.0f),
    _bIsRunning(true)
{}

void Timer::Start()
{
    if (!_bIsRunning)
    {
        _clock.restart();
        _bIsRunning = true;
    }
}

void Timer::Pause()
{
    if (_bIsRunning)
    {
        _pauseTime += _clock.getElapsedTime().asSeconds(); // Сохраняем текущее время паузы.
        _bIsRunning = false;
    }
}

void Timer::Reset()
{
    _clock.restart();
    _pauseTime = 0.0f;
    _bIsRunning = false;
}

void Timer::Restart()
{
    Reset();
    Start();
}

float Timer::GetElapsedTime() const
{
    if (!_bIsRunning)
        return _pauseTime;    

    return _pauseTime + _clock.getElapsedTime().asSeconds();
}
