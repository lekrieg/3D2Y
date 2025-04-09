#ifndef PATROL_H
#define PATROL_H

#include "Component.h"

#include "../math/Vectors.h"
#include <vector>

namespace core
{
	namespace components
	{
		class Patrol : public Component
		{
		public:

			std::vector<abyss_math::Vec2<float>> positions;
			size_t currentPosition;
			float speed;

			Patrol()
			{
			}

			Patrol(std::vector<abyss_math::Vec2<float>>& pList, float s) : positions(pList), speed(s)
			{
				currentPosition = 0;
			}
		};
	}
}

#endif // !PATROL_H
