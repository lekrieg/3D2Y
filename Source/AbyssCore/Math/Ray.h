#ifndef RAY_H
#define RAY_H

#include "Vector3D.h"
#include "Plane.h"

namespace abyss
{
	namespace math
	{
		class Ray
		{
		public:
			Ray();
			Ray(Vector3D& origin, Vector3D& dir);

			bool Intersect(Vector3D& pos, float radius, float *dist);

			bool Intersect(Vector3D& p1, Vector3D& p2,
						   Vector3D& p3, bool cull, float *dist);

			bool Intersect(Plane& pl, bool cull,
						   Vector3D *intersectPoint, float *dist);

			bool Intersect(Vector3D& bbMin, Vector3D& bbMax,
						   Vector3D *intersectPoint);

			Vector3D m_origin;
			Vector3D m_direction;
		};
	}
}

#endif