#ifndef ANIM_H
#define ANIM_H

#include "Component.h"
#include "../Animation.h"

namespace core
{
	namespace components
	{
		class Anim : public Component
		{
		public:
			Animation animation;
			bool repeat = false;

			Anim()
			{

			}

			Anim(const Animation& anim, bool r) : animation(anim), repeat(r)
			{

			}
		};
	}
}

#endif // !ANIM_H
