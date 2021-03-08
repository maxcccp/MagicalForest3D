#ifndef MB_PROGRAMMER3D_CAMERA_HPP__
#define MB_PROGRAMMER3D_CAMERA_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include <glm/glm.hpp>


namespace MBG
{

	enum CameraMovement
	{ FORWARD, BACKWARD, LEFT, RIGHT };



	class mbCamera
	{
	public:
		mbCamera();
		mbCamera(glm::vec3 pos=glm::vec3(0.0f), glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f), float yaw=-90.0f, float pitch=0.0f);
		mbCamera(float posX=0.0f, float posY=0.0f, float posZ=0.0f, float upX=0.0f, float upY=1.0f, float upZ=0.0f, float yaw=-90.0f, float pitch=0.0f);
		virtual ~mbCamera();
	public:
		const float&	GetZoom();
		glm::vec3&		GetUp();
		glm::vec3&		GetPosition();
		glm::vec3&		GetDirection();

		void Keyboard(CameraMovement direction, float deltaTime);
		void MouseMovement(float& xoffset, float& yoffset, bool constrainPitch = true);
		void MouseScroll(const float& yoffset);
		void updateCameraVectors();
	protected:
		glm::vec3 m_Direction;
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		float m_Pitch_x;
		float m_Yaw_y;
		float m_roll_z;

		float m_MovementSpeed;
		float m_MouseSensitivity;
		float m_Zoom;



	};





}



#endif
