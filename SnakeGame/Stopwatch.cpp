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
        _startTime = GetCurrentSystemTime(); // ��������� ��������� ����� � ������������ � ���������
        _bIsRunning = true;
    }
}

void Stopwatch::Pause()
{
    if (_bIsRunning)
    {
        _accumulatedTime += GetCurrentSystemTime() - _startTime; // ��������� ������� ����� �����.
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
    if (!_bIsRunning) // ��������� ����� �� ������ �� �����
        return std::chrono::duration_cast<duration>(_accumulatedTime).count(); // ���������� ���������������� �����
    
    auto seconds = std::chrono::duration_cast<duration>(_accumulatedTime + GetCurrentSystemTime() - _startTime).count();
    return seconds;
}
