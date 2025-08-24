//
// Created by lekrieg on 23/08/25.
//

#include "CustomSprite.h"

#include "SFML/System/Vector2.hpp"

// animation loops when it reaches the end
void abyss::CustomSprite::Update() // TODO: maybe I can add something like delta time here too
{
    m_currentFrame++;

    if (speed < 1)
    {
        return;
    }

    m_animFrame = (m_currentFrame / speed) % m_currentAnimation->frames.size();
    m_sprite.setTextureRect(sf::IntRect(m_currentAnimation->frames[m_animFrame]->position,
                                        sf::Vector2<int>(static_cast<int>(m_currentAnimation->frames[m_animFrame]->size.x), static_cast<int>(m_currentAnimation->frames[m_animFrame]->size.y))));

    /*
     * animFrame = (gameFrame / speed) % framecount
     * rectangle = (animFrame * fw, 0, fw, fh) -------(frame widht e frame height)
     * sprite.setTextureRect(rectangle)
     */
}

bool abyss::CustomSprite::HasEnded()
{
    return m_animFrame == (m_currentAnimation->frames.size() - 1);
}