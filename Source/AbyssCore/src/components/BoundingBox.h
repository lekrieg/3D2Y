#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Component.h"

#include <SFML/System/Vector2.hpp>

namespace core
{
	namespace components
	{
		class BoundingBox : public Component
		{
		public:
			sf::Vector2f size;
			sf::Vector2f halfSize;
			bool isTrigger;
			bool blockMove;
			bool blockVision;

			BoundingBox() : BoundingBox({ }, true)
			{
			}

			BoundingBox(const sf::Vector2f& size, bool isTrigger) : BoundingBox(size, isTrigger, false, false)
			{
			}

			BoundingBox(const sf::Vector2f& size, bool isTrigger, bool bMove, bool bVision) :
				size(size),
				halfSize(size.x / 2, size.y / 2),
				isTrigger(isTrigger),
				blockMove(bMove),
				blockVision(bVision)
			{
				isTrigger = true;
			}
		};
	}
}

#endif // !BOUNDING_BOX_H
