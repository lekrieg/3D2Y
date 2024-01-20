#ifndef MATH_DEFINES_H
#define MATH_DEFINES_H

namespace abyss
{
	namespace math
	{
		#define PI_CONST  3.14159265358979323846
		#define DEG_TO_RAD(angle)  (angle * PI_CONST / 180)
		#define RAD_TO_DEG(radian) (radian * 180 / PI_CONST)
		#define SIGN(a) (a < 0.0f) ? -1.0f : 1.0f
	}
}

#endif
