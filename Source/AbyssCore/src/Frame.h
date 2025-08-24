//
// Created by lekrieg on 22/08/25.
//

#ifndef FRAME_H
#define FRAME_H

#include "SFML/System/Vector2.hpp"

namespace abyss
{
    class Frame
    {
    public:
        sf::Vector2f size {};
        sf::Vector2f halfSize {};
        sf::Vector2i position {};

        Frame(const sf::Vector2f size, const sf::Vector2f halfSize, const sf::Vector2i position) : size(size), halfSize(halfSize), position(position)
        {

        }
    };
}

#endif //FRAME_H
