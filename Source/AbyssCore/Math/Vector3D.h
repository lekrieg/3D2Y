#ifndef VECTOR3D_H
#define VECTOR3D_H

namespace abyss
{
	namespace math
	{
		class Vector3D
		{
		public:
			float x, y, z;

			Vector3D();
			Vector3D(float x, float y, float z);
			Vector3D(const Vector3D& v);

			void Add(const Vector3D& v1, const Vector3D& v2);
			void Subtract(const Vector3D& v1, const Vector3D& v2);
			void Multiply(const Vector3D& v1, const Vector3D& v2);
			void Divide(const Vector3D& v1, const Vector3D& v2);

			void Add(const Vector3D& v1, float f);
			void Subtract(const Vector3D& v1, float f);
			void Multiply(const Vector3D& v1, float f);
			void Divide(const Vector3D& v1, float f);

			void operator=(const Vector3D& v);
			void operator+=(const Vector3D& v);
			void operator-=(const Vector3D& v);
			void operator/=(const Vector3D& v);
			void operator*=(const Vector3D& v);

			Vector3D operator+(const Vector3D& v2);
			Vector3D operator-(const Vector3D& v2);
			Vector3D operator/(const Vector3D& v2);
			Vector3D operator*(const Vector3D& v2);

			Vector3D operator+(float f);
			Vector3D operator-(float f);
			Vector3D operator/(float f);
			Vector3D operator*(float f);

			void Negate();
			float Dot3(const Vector3D& v);
			float Magnitude();

			void Normalize();
			void Normalize(Vector3D p1, Vector3D p2, Vector3D p3);

			Vector3D CrossProduct(const Vector3D& v);
		};
	}
}


#endif