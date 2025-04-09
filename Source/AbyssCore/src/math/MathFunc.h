#ifndef MATH_FUNC_H
#define MATH_FUNC_H

namespace core
{
	namespace mathFunc
	{
		float lerp(float a, float b, float t)
		{
			return a * (1.0f - t) + (b * t);
		}
	}
}

#endif // !MATH_FUNC_H
