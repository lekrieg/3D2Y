#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3D.h"

namespace abyss
{
	namespace math
	{
		class Quaternion
		{
		public:
			Quaternion();
			Quaternion(const Quaternion &q);
			Quaternion(float X, float Y, float Z, float W);

			Quaternion operator*(const Quaternion &q);
			void operator=(const Quaternion &q);

			float Magnitude();
			void Normalize();
			Quaternion Conjugate();

			void RotationAxisToQuaternion(float angle, Vector3D &axis);
			void EulerToQuaternion(Vector3D &euler);

			Quaternion CrossProduct(const Quaternion &q);

			void CreateMatrix(float *matrix);
			void MatrixToQuaternion(float *matrix);

			void Slerp(const Quaternion &q1, const Quaternion &q2, float t);

			float w, y, z, x;
		};
	}
}

#endif