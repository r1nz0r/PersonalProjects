#include "Application.h"

Application& Application::GetInstance()
{
    static Application sApplication;
    return sApplication;
}
