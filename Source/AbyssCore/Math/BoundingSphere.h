#ifndef BOUNDING_SPHERE_h
#define BOUNDING_SPHERE_h

#include "Vector3D.h"
#include "BoundingBox.h"

namespace abyss
{
	namespace math
	{
		class BoundingSphere
		{
		public:
			Vector3D m_center;
			double m_radius;

			BoundingSphere();
			BoundingSphere(BoundingSphere& bs);

			void Calculate(Vector3D* v, int numPoints);
			void Translate(Vector3D v);

			bool CollisionCheck(BoundingSphere& bs);
			bool CollisionCheck(Vector3D& v);
			bool CollisionCheck(Vector3D& p1, Vector3D& p2, Vector3D& p3);
			bool CollisionCheck(BoundingBox& aabb);
		};
	}
}

#endif