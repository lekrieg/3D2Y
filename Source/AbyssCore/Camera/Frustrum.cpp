#include "Frustrum.h"

#include <cmath>

namespace abyss
{
	namespace camera
	{
		Frustum::Frustum()
		{
		}

		void Frustum::CalculateFrustum(float angle, float ratio, float near, float far, math::Vector3D& camPos, math::Vector3D& lookAt, math::Vector3D& up)
		{
			math::Vector3D xVec, yVec, zVec;
			math::Vector3D vecN, vecF;
			math::Vector3D nearTopLeft, nearTopRight, nearBottomLeft, nearBottomRight;
			math::Vector3D farTopLeft, farTopRight, farBottomLeft, farBottomRight;

			float radians = static_cast<float>(tan((DEG_TO_RAD(angle)) * 0.5));
			float nearH = near * radians;
			float nearW = nearH * ratio;
			float farH = far * radians;
			float farW = farH * ratio;

			zVec = camPos - lookAt;
			zVec.Normalize();

			xVec = up.CrossProduct(zVec);
			xVec.Normalize();

			yVec = zVec.CrossProduct(xVec);

			vecN = camPos - zVec * near;
			vecF = camPos - zVec * far;

			nearTopLeft = vecN + yVec * nearH - xVec * nearW;
			nearTopRight = vecN + yVec * nearH + xVec * nearW;
			nearBottomLeft = vecN - yVec * nearH - xVec * nearW;
			nearBottomRight = vecN - yVec * nearH + xVec * nearW;

			farTopLeft = vecF + yVec * farH - xVec * farW;
			farTopRight = vecF + yVec * farH + xVec * farW;
			farBottomLeft = vecF - yVec * farH - xVec * farW;
			farBottomRight = vecF - yVec * farH + xVec * farW;

			m_frustum.clear();

			math::Plane plane;

			plane.CreatePlaneFromTri(nearTopRight, nearTopLeft, farTopLeft);
			AddPlane(plane);

			plane.CreatePlaneFromTri(nearBottomLeft, nearBottomRight, farBottomRight);
			AddPlane(plane);

			plane.CreatePlaneFromTri(nearTopLeft, nearBottomLeft, farBottomLeft);
			AddPlane(plane);

			plane.CreatePlaneFromTri(nearBottomRight, nearTopRight, farBottomRight);
			AddPlane(plane);

			plane.CreatePlaneFromTri(nearTopLeft, nearTopRight, nearBottomRight);
			AddPlane(plane);

			plane.CreatePlaneFromTri(farTopRight, farTopLeft, farBottomLeft);
			AddPlane(plane);
		}

		void Frustum::AddPlane(math::Plane& pl)
		{
			m_frustum.push_back(pl);
		}

		bool Frustum::GetPlane(int index, math::Plane* out)
		{
			if (out == 0 || index >= (int)m_frustum.size() || index < 0)
			{
				return false;
			}

			*out = m_frustum[index];

			return true;
		}

		bool Frustum::isPointVisible(float x, float y, float z)
		{
			for (int i = 0; i < static_cast<int>(m_frustum.size()); i++)
			{
				if (m_frustum[i].GetDistance(x, y, z) < 0)
				{
					return false;
				}
			}

			return true;
		}

		bool Frustum::isSphereVisible(float x, float y, float z, float radius)
		{
			float distance = 0;

			for (int i = 0; i < static_cast<int>(m_frustum.size()); i++)
			{
				distance = m_frustum[i].GetDistance(x, y, z);

				if (distance < -radius)
				{
					return false;
				}
			}

			return true;
		}

		bool Frustum::isCubeVisible(float x, float y, float z, float size)
		{
			float minX, maxX;
			float minY, maxY;
			float minZ, maxZ;

			minX = x - size;
			maxX = x + size;
			minY = y - size;
			maxY = y + size;
			minZ = z - size;
			maxZ = z + size;

			return isBoxVisible(math::Vector3D(minX, minY, minZ), math::Vector3D(maxX, maxY, maxZ));
		}

		bool Frustum::isBoxVisible(math::Vector3D min, math::Vector3D max)
		{
			if (isPointVisible(min.x, min.y, min.z) ||
				isPointVisible(max.x, min.y, min.z) ||
				isPointVisible(min.x, max.y, min.z) ||
				isPointVisible(max.x, max.y, min.z) ||
				isPointVisible(min.x, min.y, max.z) ||
				isPointVisible(max.x, min.y, max.z) ||
				isPointVisible(min.x, max.y, max.z) ||
				isPointVisible(max.x, max.y, max.z))
			{
				return true;
			}

			return false;
		}

		bool Frustum::isOrientedBoundingBoxVisible(math::OrientedBoundingBox& obb)
		{
			math::Vector3D n;
			float radius = 0.0f;

			for (int i = 0; i < (int)m_frustum.size(); i++)
			{
				n = math::Vector3D(m_frustum[i].a, m_frustum[i].b, m_frustum[i].c);
				n = n * -1;

				float r = fabs(obb.m_halfAxis1 * (n.Dot3(obb.m_axis1))) +
						  fabs(obb.m_halfAxis2 * (n.Dot3(obb.m_axis2))) +
						  fabs(obb.m_halfAxis3 * (n.Dot3(obb.m_axis3)));

				if (n.Dot3((obb.m_center - m_frustum[i].d)) < -r)
				{
					return false;
				}
			}

			return true;
		}
	}
}