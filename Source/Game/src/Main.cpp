#include "GameApplication.h"

int main()
{
	game::GameApplication game("config.txt", "test.asset");
	game.Run();
}
