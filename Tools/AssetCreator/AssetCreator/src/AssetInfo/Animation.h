//
// Created by lekrieg on 22/07/25.
//

#ifndef FRAME_H
#define FRAME_H
#include <vector>

#include "SFML/System/Vector2.hpp"

namespace abyss
{
    namespace asset_info
    {
        class Animation
        {
        public:

            char name[128] = {"Default"};

            std::vector<sf::Vector2f> size {};
            std::vector<sf::Vector2f> halfSize {};
            std::vector<sf::Vector2i> position {};

            Animation() = default;

            explicit Animation(const sf::Vector2f& size)
            {
                AddFrame(size);
            }

            void AddFrame(const sf::Vector2f& size)
            {
                this->size.push_back(size);
                this->halfSize.push_back(size / 2.0f);
                this->position.push_back(sf::Vector2i(0, 0));
            }

            void SetSize(const sf::Vector2f& size, const int index)
            {
                this->size[index].x = size.x;
                this->size[index].y = size.y;
                this->halfSize[index].x = size.x / 2.0f;
                this->halfSize[index].y = size.y/ 2.0f;
            }
        };
    }
}

#endif //FRAME_H
