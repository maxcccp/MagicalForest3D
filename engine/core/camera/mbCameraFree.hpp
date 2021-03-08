#ifndef MB_PROGRAMMER3D_CAMERAFREE_HPP__
#define MB_PROGRAMMER3D_CAMERAFREE_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include "mbCamera.hpp"


namespace MBG
{

	class mbCameraFree : public mbCamera
	{
	public:

		mbCameraFree(float x=0.0f, float y=0.0f, float z=0.0f);
		virtual ~mbCameraFree();

		void Translate(const float &deltaTime);

		const glm::mat4& GetView();
		const glm::mat4& GetProj();

	private:

		float lastX;
		float lastY;
		static float PosX;
		static float PosY;

		glm::mat4 m_view;
		glm::mat4 m_projection;
	};

}
#endif
