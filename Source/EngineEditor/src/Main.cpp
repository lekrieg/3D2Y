#include "GameApplication.h"

int main()
{
	core::GameApplication game("config.txt", "assets.txt");
	game.Run();
}