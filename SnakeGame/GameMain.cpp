#include "Application.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

int main()
{
	Application& app = Application::GetInstance();
	app.Run();
	return 0;
}