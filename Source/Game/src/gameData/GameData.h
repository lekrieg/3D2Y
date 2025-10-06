//
// Created by lekrieg on 04/09/25.
//

#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <vector>

#include "GameData.h"
#include "SFML/System/Vector2.hpp"

namespace game
{
    enum class AiType;

    struct PlayerInfo
    {
        float speed;
        float maxSpeed;
    };

    enum class AiType
    {
        Follow,
        Patrol,
    };

    struct AiInfo
    {
        AiType type;
        float speed;
        std::vector<sf::Vector2f> patrolPositions;
    };

    struct NpcInfo
    {
        float speed = 0;
        bool blockMove = false;
        bool blockVision = false;
        int maxHealth = 0;
        int damage = 0;
        AiInfo aiInfo;
    };
}

#endif //GAME_DATA_H
