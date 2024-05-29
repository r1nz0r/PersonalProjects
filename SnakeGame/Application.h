#pragma once
#include "SFML/Graphics.hpp"

class Game;
class Menu;
class TextInputBox;

// The main application class responsible for managing the game loop and application lifecycle.
class Application
{
public:
    Application(const Application& other) = delete;
    Application(Application&& other) noexcept = delete;
    Application& operator=(const Application& other) = delete;
    Application& operator=(Application&& other) = delete;

    // Returns a reference to the singleton instance of Application.
    static Application& GetInstance();

    // Starts the application's main loop.
    void Run();

    // Clears the resources used by the application.
    void Clear();

    // Returns a pointer to the current game instance.
    Game* GetGame() const { return _game; }

private:
    Game* _game; // Pointer to the current game instance.
    
    // Private constructor to prevent instantiation.
    Application() = default;

    ~Application();
};
