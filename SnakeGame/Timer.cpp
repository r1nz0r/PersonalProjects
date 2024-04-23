#include "Timer.h"

Timer::Timer()
    : _clock(),
    _runTime(0.0f),
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
        _runTime += _clock.getElapsedTime().asSeconds(); // Сохраняем текущее время паузы.
        _bIsRunning = false;
    }
}

//void Timer::Resume()
//{
//    if (!_bIsRunning)
//    {
//        float pauseDuration = _clock.getElapsedTime().asSeconds() - _runTime; // Вычисляем время, прошедшее с момента паузы.
//        _runTime += pauseDuration; // Добавляем это время к общему времени паузы.
//        _bIsRunning = true;
//    }
//}

void Timer::Reset()
{
    _clock.restart();
    _runTime = 0.0f;
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
        return _runTime;    

    return _runTime + _clock.getElapsedTime().asSeconds();
}
