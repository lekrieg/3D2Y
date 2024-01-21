#include "BoundingSphere.h"

#include <cmath>

namespace abyss
{
	namespace math
	{
		BoundingSphere::BoundingSphere()
		{
			m_radius = 0;
		}

		BoundingSphere::BoundingSphere(BoundingSphere& bs)
		{
			m_center = bs.m_center;
			m_radius = bs.m_radius;
		}

		void BoundingSphere::Calculate(Vector3D* v, int numPoints)
		{
			float distance = 0.0f;
			float tempDist = 0.0f;

			for (int i = 0; i < numPoints; i++)
			{

				tempDist = ((v[i].x - m_center.x) * (v[i].x - m_center.x)) +
						   ((v[i].y - m_center.y) * (v[i].y - m_center.y)) +
						   ((v[i].z - m_center.z) * (v[i].z - m_center.z));

				if (tempDist > distance)
				{
					distance = tempDist;
				}
			}

			m_radius = sqrt(distance);
		}

		void BoundingSphere::Translate(Vector3D v)
		{
			m_center += v;
		}

		bool BoundingSphere::CollisionCheck(BoundingSphere& bs)
		{
			Vector3D vec = m_center - bs.m_center;

			if (sqrt(vec.Dot3(vec)) < m_radius + bs.m_radius)
			{
				return true;
			}

			return false;
		}

		bool BoundingSphere::CollisionCheck(Vector3D& p1)
		{
			Vector3D vec = m_center - p1;

			if (sqrt(vec.Dot3(vec)) < m_radius + 0.01f)
			{
				return true;
			}

			return false;
		}

		bool BoundingSphere::CollisionCheck(Vector3D& p1, Vector3D& p2, Vector3D& p3)
		{
			if (CollisionCheck(p1) ||
				CollisionCheck(p2) ||
				CollisionCheck(p3))
			{
				return true;
			}

			return false;
		}

		bool BoundingSphere::CollisionCheck(BoundingBox& aabb)
		{
			Vector3D b(aabb.m_min.x, aabb.m_max.y, aabb.m_min.z);
			Vector3D c(aabb.m_max.x, aabb.m_max.y, aabb.m_min.z);
			Vector3D d(aabb.m_max.x, aabb.m_min.y, aabb.m_min.z);
			Vector3D e(aabb.m_min.x, aabb.m_min.y, aabb.m_max.z);
			Vector3D f(aabb.m_min.x, aabb.m_max.y, aabb.m_max.z);
			Vector3D h(aabb.m_max.x, aabb.m_min.y, aabb.m_max.z);

			if (CollisionCheck(aabb.m_min) ||
				CollisionCheck(b) ||
				CollisionCheck(c) ||
				CollisionCheck(d) ||
				CollisionCheck(e) ||
				CollisionCheck(f) ||
				CollisionCheck(aabb.m_max) ||
				CollisionCheck(h))
			{
				return true;
			}

			return false;
		}
	}
}