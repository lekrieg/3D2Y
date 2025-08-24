//
// Created by lekrieg on 22/08/25.
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"

#include <memory>

#include "assets/BaseAsset.h"

namespace abyss
{
    class Animation
    {
    public:
        char name[128] = {"Default"};

        std::vector<std::shared_ptr<Frame>> frames;

        Animation() = default;

        void AddFrame(const sf::Vector2f &size, const sf::Vector2i &pos)
        {
            frames.push_back(std::make_shared<Frame>(size, size / 2.0f, pos));
        }

        void SetSize(const std::shared_ptr<Frame> &frame, const sf::Vector2f &size)
        {
            frame->size.x = size.x;
            frame->size.y = size.y;
            frame->halfSize.x = size.x / 2.0f;
            frame->halfSize.y = size.y / 2.0f;
        }
    };
}

#endif //ANIMATION_H
