#ifndef ORIENTED_BOUNDING_BOX_H
#define ORIENTED_BOUNDING_BOX_H

#include "Vector3D.h"
#include "BoundingBox.h"
#include "Matrix4x4.h"
#include "Polytope.h"

namespace abyss
{
	namespace math
	{
		class OrientedBoundingBox : public Polytope
		{
		public:
			Vector3D m_center;
			float m_halfAxis1, m_halfAxis2, m_halfAxis3;
			Vector3D m_axis1, m_axis2, m_axis3;

			OrientedBoundingBox();
			OrientedBoundingBox(OrientedBoundingBox& obb);
			OrientedBoundingBox(BoundingBox& aabb);

			void Calculate(Vector3D* vertices, int numVerts);
			void Calculate(BoundingBox& aabb);

			void Transform(OrientedBoundingBox& obb, Matrix4x4& mat);
			void ObjectTransform(OrientedBoundingBox& obb, Matrix4x4& mat);

			void ProjectionInterval(Vector3D& axis, float& center, float& ext, float& min, float& max);

			unsigned int GetSupport(Vector3D& axis, Vector3D* contacts); const

			Vector3D GetFaceNormal(int index) const
			{
				if (index == 0)
				{
					return m_axis1;
				}

				else if (index == 1)
				{
					return m_axis2;
				}

				return m_axis3;
			}

			Vector3D GetEdgeDirection(int index) const
			{
				return GetFaceNormal(index);
			}

			Vector3D GetCenterPos() const { return m_center; };
			void SetCenter(Vector3D& center) { m_center = center; }

			float GetHalfAxis1() const { return m_halfAxis1; }
			float GetHalfAxis2() const { return m_halfAxis2; }
			float GetHalfAxis3() const { return m_halfAxis3; }

			float GetHalfAxis(int index) const
			{
				if (index == 0)
				{
					return m_halfAxis1;
				}
				else if (index == 1)
				{
					return m_halfAxis2;
				}

				return m_halfAxis3;
			}

			void SetHalfAxis1(float val) { m_halfAxis1 = val; }
			void SetHalfAxis2(float val) { m_halfAxis2 = val; }
			void SetHalfAxis3(float val) { m_halfAxis3 = val; }

			Vector3D GetAxis1() const { return m_axis1; }
			Vector3D GetAxis2() const { return m_axis2; }
			Vector3D GetAxis3() const { return m_axis3; }

			Vector3D GetAxis(int index) const
			{
				if (index == 0)
				{
					return m_axis1;
				}
				else if (index == 1)
				{
					return m_axis2;
				}

				return m_axis3;
			}

			void SetAxis1(Vector3D& axis) { m_axis1 = axis; }
			void SetAxis2(Vector3D& axis) { m_axis2 = axis; }
			void SetAxis3(Vector3D& axis) { m_axis3 = axis; }
		};
	}
}

#endif