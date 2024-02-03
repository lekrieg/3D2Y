#include "Application.h"

#include <iostream>

int main(int argc, char* argv[])
{
	Application app;
	if(!app.Initialize())
	{
		std::cout << "Error in initialize" << '\n';
	}

	while(!app.ShouldCloseWindow())
	{
		app.Update();
		app.Render();
	}

	app.Shutdown();
    
    return 0;
}
