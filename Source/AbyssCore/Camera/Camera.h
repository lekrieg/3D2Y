#ifndef CAMERA_H
#define CAMERA_H

#include "../Math/Vector3D.h"

namespace abyss
{
	namespace camera
	{
		class Camera
		{
		public:
			Camera();

			Camera(math::Vector3D &pos, math::Vector3D &lookAt,
				   math::Vector3D &up, math::Vector3D &right);

			void MoveCamera(math::Vector3D &direction, float speed);
			void StrafeCam(float speed);

			void RotateCamera(float angle, math::Vector3D &axis);
			void RotateCamera(float deltaX, float deltaY);

			void SetPosition(math::Vector3D &pos) { m_pos = pos; }
			void SetLookDirection(math::Vector3D &at) { m_lookAt = at; }
			void SetUpDirection(math::Vector3D &up) { m_up = up; }
			void SetRightDirection(math::Vector3D &right) { m_right = right; }

			math::Vector3D GetPosition() { return m_pos; }
			math::Vector3D GetLookDirection() { return m_lookAt; }
			math::Vector3D GetUpDirection() { return m_up; }
			math::Vector3D GetRightDirection() { return m_right; }

		private:
			math::Vector3D m_pos, m_lookAt, m_up, m_right;
		};
	}
}

#endif