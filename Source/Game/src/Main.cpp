#include "GameApplication.h"

int main()
{
	game::GameApplication game("config.txt", "assets.txt");
	game.Run();
}
