#pragma once
#include <SFML/System.hpp>

class Timer
{
public:
    explicit Timer();

    void Start();
    void Pause();
    void Reset();
    void Restart();
    bool IsRunning() const { return _bIsRunning; }
    float GetElapsedTime() const; // Возвращает время в секундах

private:
    sf::Clock _clock;
    float _pauseTime;
    bool _bIsRunning;
};