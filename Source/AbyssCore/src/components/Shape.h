#ifndef SHAPE_H
#define SHAPE_H

#include "Component.h"

#include <SFML/Graphics.hpp>

namespace core
{
	namespace components
	{
		class Shape : public Component
		{
		public:
			sf::CircleShape shape;

			Shape() : Shape(0, 0, sf::Color(), sf::Color(), 0)
			{

			}

			Shape(float radius, int pointCount, const  sf::Color& fill, const sf::Color& outline, float thickness) : shape(radius, pointCount)
			{
				shape.setFillColor(fill);
				shape.setOutlineColor(outline);
				shape.setOutlineThickness(thickness);
				shape.setOrigin(radius, radius);
			}
		};
	}
}

#endif // !SHAPE_H
