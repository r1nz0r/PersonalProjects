#include <iostream>
#include <thread>
#include "Application.h"
#include "Stopwatch.h"

int main()
{
    Application& app = Application::GetInstance();
    app.Run();
    return 0;
}


