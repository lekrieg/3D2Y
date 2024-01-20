#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Vector3D.h"

namespace abyss
{
	namespace math
	{
		class BoundingBox
		{
		public:

			Vector3D m_min, m_max, m_center;

			BoundingBox();
			BoundingBox(const BoundingBox& aabb);

			void Calculate(Vector3D* v, int numPoints);
			void Expand(float amt);

			void Translate(Vector3D v);

			bool CollisionCheck(const BoundingBox& aabb);
			bool CollisionCheck(const Vector3D& v);

			void operator=(BoundingBox b)
			{
				m_min = b.m_min;
				m_max = b.m_max;
				m_center = b.m_center;
			}
		};
	}
}

#endif