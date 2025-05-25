#ifndef ANIM_H
#define ANIM_H

#include "Component.h"
#include "../Animation.h"

namespace abyss
{
	namespace components
	{
		class Anim : public Component
		{
		public:
			Animation animation;
			bool repeat = false;

			Anim() = default;

			Anim(const Animation& anim, const bool r) : animation{ anim }, repeat(r)
			{

			}
		};
	}
}

#endif // !ANIM_H
