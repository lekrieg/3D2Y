#include "BoundingBox.h"

namespace abyss
{
	namespace math
	{
		BoundingBox::BoundingBox()
		{
		}

		BoundingBox::BoundingBox(const BoundingBox& aabb)
		{
			m_min = aabb.m_min;
			m_max = aabb.m_max;
			m_center = aabb.m_center;
		}

		void BoundingBox::Calculate(Vector3D* v, int numPoints)
		{
			for (int i = 0; i < numPoints; i++)
			{
				if (v[i].x < m_min.x)
				{
					m_min.x = v[i].x;
				}

				if (v[i].x > m_max.x)
				{
					m_max.x = v[i].x;
				}

				if (v[i].y < m_min.y)
				{
					m_min.y = v[i].y;
				}

				if (v[i].y > m_max.y)
				{
					m_max.y = v[i].y;
				}

				if (v[i].z < m_min.z)
				{
					m_min.z = v[i].z;
				}

				if (v[i].z > m_max.z)
				{
					m_max.z = v[i].z;
				}
			}

			m_center.x = (m_min.x + m_max.x) * 0.5f;
			m_center.y = (m_min.y + m_max.y) * 0.5f;
			m_center.z = (m_min.z + m_max.z) * 0.5f;
		}

		void BoundingBox::Expand(float amt)
		{
			m_max.x = m_max.x + amt;
			m_min.x = m_min.x - amt;
			m_max.y = m_max.y + amt;
			m_min.y = m_min.y - amt;
			m_max.z = m_max.z + amt;
			m_min.z = m_min.z - amt;
		}

		void BoundingBox::Translate(Vector3D v)
		{
			m_min += v;
			m_max += v;
			m_center += v;
		}

		bool BoundingBox::CollisionCheck(const BoundingBox& aabb)
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

		bool BoundingBox::CollisionCheck(const Vector3D& v)
		{
			if ((m_max.x <= v.x) ||
				(m_min.x >= v.x) ||
				(m_max.y <= v.y) ||
				(m_min.y >= v.y) ||
				(m_max.z <= v.z) ||
				(m_min.z >= v.z))
			{
				return false;
			}

			return true;
		}
	}
}