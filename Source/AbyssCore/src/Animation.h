#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

namespace abyss
{
	class Animation
	{
			sf::Sprite m_sprite;

			int m_frameCount;
			int m_currentFrame;
			int m_animFrame;
			int m_speed;
			sf::Vector2f m_size;
			sf::Vector2f m_halfSize;
			std::string m_name;

		public:

		    Animation() : Animation("", sf::Texture())
			{
			}

			Animation(const std::string &name, const sf::Texture &texture) : Animation(name, texture, 1, 0)
			{
			}

			Animation(const std::string &name, const sf::Texture &texture, int frameCount, int speed) :
				m_name(name),
				m_speed(speed),
				m_currentFrame(0),
				m_sprite(texture),
				m_frameCount(frameCount),
				m_animFrame(0)
			{
				m_currentFrame = 0;
				m_size = sf::Vector2f(static_cast<float>(texture.getSize().x / frameCount),
									  static_cast<float>(texture.getSize().y));
				m_halfSize = sf::Vector2f(m_size.x / 2.0f, m_size.y / 2.0f);
				m_sprite.setOrigin(sf::Vector2f(m_size.x / 2.0f, m_size.y / 2.0f));
				m_sprite.setTextureRect(sf::IntRect(
					sf::Vector2<int>(static_cast<int>(std::floor(m_currentFrame)) * static_cast<int>(m_size.x), 0),
					sf::Vector2<int>(static_cast<int>(m_size.x), static_cast<int>(m_size.y))));
			}

			void Update();
			bool HasEnded();

			sf::Sprite &GetSprite()
			{
				return m_sprite;
			}

			const sf::Vector2f &GetSize() const
			{
				return m_size;
			}

			const sf::Vector2f &GetHalfSize() const
			{
				return m_halfSize;
			}

			const std::string &GetName() const
			{
				return m_name;
			}
	};
}

#endif // !ANIMATION_H
