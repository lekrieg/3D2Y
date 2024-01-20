#ifndef PLANE_H
#define PLANE_H

#include "Vector3D.h"
#include "OrientedBoundingBox.h"

namespace abyss
{
	namespace math
	{
		enum class ABYSS_PLANE_STATUS
		{
			ABYSS_PLANE_FRONT = 1,
			ABYSS_PLANE_BACK,
			ABYSS_PLANE_ON_PLANE,
			ABYSS_PLANE_CLIPPED,
			ABYSS_PLANE_CULLED,
			ABYSS_PLANE_VISIBLE
		};

		class Plane
		{
		public:
			Plane();
			Plane(float A, float B, float C, float D);

			void CreatePlaneFromTri(Vector3D &t1,
									Vector3D &t2,
									Vector3D &t3);

			bool Intersect(const Plane &pl, Vector3D *intersectPoint);
			bool Intersect(const Vector3D &bbMin, const Vector3D &bbMax);
			bool Intersect(const Vector3D &position, float radius);
			bool Intersect(const OrientedBoundingBox &obb);

			ABYSS_PLANE_STATUS ClassifyPoint(const Vector3D &v);
			ABYSS_PLANE_STATUS ClassifyPoint(const Vector3D &v, float *dist);
			ABYSS_PLANE_STATUS ClassifyPoint(float x, float y, float z);
			ABYSS_PLANE_STATUS ClassifyPoint(float x, float y, float z, float *dist);

			float GetDistance(const Vector3D &v);
			float GetDistance(float x, float y, float z);

			Vector3D Reflect(Vector3D vec, float e);

			bool ClipTriangle(Vector3D *inVerts, int totalInVerts,
							  Vector3D *outFrontVerts, int *totalOutFrontVerts,
							  Vector3D *outBackVerts, int *totalOutBackVerts);

			Vector3D GetNormal()
			{
				return Vector3D(a, b, c);
			}

			void SetNormal(Vector3D n)
			{
				a = n.x;
				b = n.y;
				c = n.z;
			}

			void SetPointOnPlane(Vector3D p)
			{
				m_pointOnPlane = p;
			}

			bool operator==(Plane p)
			{
				return (a == p.a && b == p.b &&
						c == p.c && d == p.d);
			}

			void operator=(Plane p)
			{
				a = p.a;
				b = p.b;
				c = p.c;
				d = p.d;
			}

			float a, b, c, d;
			Vector3D m_pointOnPlane;
		};
	}
}

#endif