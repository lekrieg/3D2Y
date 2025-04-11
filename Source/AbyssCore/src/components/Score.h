#ifndef SCORE_H
#define SCORE_H

#include "Component.h"

namespace abyss
{
	namespace components
	{
		class Score : public Component
		{
		public:
			int score;

			Score() : Score(0)
			{

			}

			Score(int s) : score(s)
			{
			}
		};
	}
}

#endif // !SCORE_H
