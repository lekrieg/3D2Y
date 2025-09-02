#ifndef ANIM_H
#define ANIM_H

#include <utility>

#include "Component.h"
#include "../CustomSprite.h"

namespace abyss
{
	namespace components
	{
		class Anim : public Component
		{
		public:
			CustomSprite animation;
			bool repeat = false;
			bool shouldDraw = true;

			Anim(CustomSprite  anim, const bool r) : animation{std::move( anim )}, repeat(r)
			{
			}
		};
	}
}

#endif // !ANIM_H
