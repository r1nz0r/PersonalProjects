#include "Application.h"

Application& Application::GetInstance()
{
    static Application sApplication;
    return sApplication;
}

Application::Application()
{}

Application::~Application()
{
    delete _game;
}
