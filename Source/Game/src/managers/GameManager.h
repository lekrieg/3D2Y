#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "vector"

namespace game
{
	class GameManager
	{
	public:
		int sceneIndex = 0;
		std::vector<bool> clearedLevels = { false, false, false, false, false };
	};
}

#endif // !GAME_MANAGER_H
