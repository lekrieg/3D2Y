//
// Created by lekrieg on 22/07/25.
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>

#include "Frame.h"

class Animation
{
public:

    char name[128] = {"Default"};

    std::vector<std::shared_ptr<Frame>> frames;

    bool isActive = true;

    Animation() = default;

    explicit Animation(const sf::Vector2f& size)
    {
        AddFrame(size);
    }

    void AddFrame(const sf::Vector2f& size)
    {
        frames.push_back(std::make_shared<Frame>(size, size / 2.0f, sf::Vector2i(0, 0)));
    }

    void SetSize(const std::shared_ptr<Frame>& frame, const sf::Vector2f& size)
    {
        frame->size.x = size.x;
        frame->size.y = size.y;
        frame->halfSize.x = size.x / 2.0f;
        frame->halfSize.y = size.y/ 2.0f;
    }
};

#endif //ANIMATION_H
