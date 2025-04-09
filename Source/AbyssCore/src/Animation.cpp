#include "Animation.h"
#include "SFML/System/Vector2.hpp"

// animation loops when it reaches the end
void core::Animation::Update()
{
	m_currentFrame++;

	if (m_speed < 1)
	{
		return;
	}

	m_animFrame = (m_currentFrame / m_speed) % m_frameCount;
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2<int>(m_animFrame * static_cast<int>(m_size.x), 0),
										sf::Vector2<int>(static_cast<int>(m_size.x), static_cast<int>(m_size.y))));

	/*
	 * animFrame = (gameFrame / speed) % framecount
	 * rectangle = (animFrame * fw, 0, fw, fh) -------(frame widht e frame height)
	 * sprite.setTextureRect(rectangle)
	 */
}

bool core::Animation::HasEnded()
{
	return m_animFrame == (m_frameCount - 1);
}
