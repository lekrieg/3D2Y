#ifndef FOLLOW_PLAYER_H
#define FOLLOW_PLAYER_H

#include "Component.h"

#include "../math/Vectors.h"

namespace core
{
	namespace components
	{
		class FollowPlayer : public Component
		{
		public:
			
			abyss_math::Vec2<float> home;
			float speed;

			FollowPlayer() : FollowPlayer(abyss_math::Vec2<float>(0, 0), 0)
			{
			}

			FollowPlayer(abyss_math::Vec2<float> p, float s) : home(p), speed(s)
			{
			}
		};
	}
}

#endif // !FOLLOW_PLAYER_H