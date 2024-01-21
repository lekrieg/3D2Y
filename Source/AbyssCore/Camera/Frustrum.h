#ifndef FRUSTRUM_H
#define FRUSTRUM_H

#include "../Math/Vector3D.h"
#include "../Math/OrientedBoundingBox.h"
#include "../Math/Plane.h"

#include <vector>

namespace abyss
{
	namespace camera
	{
		class Frustum
		{
		private:
			std::vector<math::Plane> m_frustum;

		public:
			Frustum();

			void CalculateFrustum(float angle, float ratio, float near, float far, math::Vector3D& camPos, math::Vector3D& lookAt, math::Vector3D& up);

			void AddPlane(math::Plane& pl);
			bool GetPlane(int index, math::Plane* out); const
			int GetTotalPlanes() const { return (int)m_frustum.size(); }

			bool isPointVisible(float x, float y, float z);
			bool isSphereVisible(float x, float y, float z, float radius);
			bool isCubeVisible(float x, float y, float z, float size);
			bool isBoxVisible(math::Vector3D min, math::Vector3D max);
			bool isOrientedBoundingBoxVisible(math::OrientedBoundingBox& obb);
		};
	}
}

#endif