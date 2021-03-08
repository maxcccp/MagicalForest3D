#include "mbCamera.hpp"


#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;
using namespace glm;




namespace MBG
{


	// (NOTE) mb_software: mb_software: Constructor.
	mbCamera::mbCamera()
	{}


	// (NOTE) mb_software: ����������� � ���������
	mbCamera::mbCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(2.0f), m_MouseSensitivity(0.20f), m_Zoom(45.0f)
	{

		this->m_Position = position;
		this->m_WorldUp = up;
		this->m_Pitch_x = pitch;
		this->m_Yaw_y = yaw;

		this->updateCameraVectors();
	}


	// (NOTE) mb_software: ����������� �� ���������� ����������
	mbCamera::mbCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(2.0f), m_MouseSensitivity(0.25f), m_Zoom(45.0f)
	{
		this->m_Position = glm::vec3(posX, posY, posZ);
		this->m_WorldUp = glm::vec3(upX, upY, upZ);
		this->m_Pitch_x = pitch;
		this->m_Yaw_y = yaw;

		this->updateCameraVectors();
	}


	// (NOTE) mb_software: ����������
	mbCamera::~mbCamera()
	{
	}


	// (NOTE) mb_software: ������� ������ ������������ �����.
	glm::vec3 & mbCamera::GetUp()
	{
		return m_Up;
	}

	// (NOTE) mb_software: �������� ���� ��������� ������.
	const float& mbCamera::GetZoom() 
	{ 
		return m_Zoom; 
	}

	// (NOTE) mb_software: ������ ������� ������ � �����.
	glm::vec3&  mbCamera::GetPosition()
	{ 
		return m_Position; 
	}

	// (NOTE) mb_software: ������ ����������� ���� ������� ������.
	glm::vec3& mbCamera::GetDirection()
	{
		return m_Direction;
	}


	// (NOTE) mb_software:
	// �������� �����, ���������� �� ����� ���������� ������� �����.
	// ��������� ������� �������� � ���� ������, ������������ ENUM (��� ��������������� �� ������� ������)
	void  mbCamera::Keyboard(CameraMovement direction, float deltaTime)
	{
		float velocity = this->m_MovementSpeed * deltaTime;
		if (direction == FORWARD)
			this->m_Position += this->m_Front * velocity;
		if (direction == BACKWARD)
			this->m_Position -= this->m_Front * velocity;
		if (direction == LEFT)
			this->m_Position -= this->m_Right * velocity;
		if (direction == RIGHT)
			this->m_Position += this->m_Right * velocity;
	}


	//(NOTE) mb_software:
	// �������� �����, ���������� �� ������� ����� ����. ������� �������� �������� ��� � ����������� x, ��� � � y.
	void  mbCamera::MouseMovement(float& xset, float& yset, bool constrainPitch)
	{
		xset *= this->m_MouseSensitivity;
		yset *= this->m_MouseSensitivity;

		this->m_Yaw_y += xset;
		this->m_Pitch_x += yset;

		// ��������������, ���, ����� ������ ��� �������, ����� �� �������� ������������
		if (constrainPitch)
		{
			if (this->m_Pitch_x > 89.0f)
				this->m_Pitch_x = 89.0f;
			if (this->m_Pitch_x < -89.0f)
				this->m_Pitch_x = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		this->updateCameraVectors();
	}



	// (NOTE) mb_software: �������� �����, ���������� �� ������� ��������� ����. ��������� ������ ���� �� ������������ ��� ������
	void  mbCamera::MouseScroll(const float& yoffset)
	{
		if (this->m_Zoom >= 1.0f && this->m_Zoom <= 45.0f)
			this->m_Zoom -= yoffset * 15.0f; // 3x ������� zoom
		if (this->m_Zoom <= 1.0f)
			this->m_Zoom = 1.0f;
		if (this->m_Zoom >= 45.0f)
			this->m_Zoom = 45.0f;
	}



	// (NOTE) mb_software: ��������� �����-������ �� ����� ������ (�����������)
	void  mbCamera::updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(this->m_Yaw_y)) * cos(glm::radians(this->m_Pitch_x));
		front.y = sin(glm::radians(this->m_Pitch_x));
		front.z = sin(glm::radians(this->m_Yaw_y)) * cos(glm::radians(this->m_Pitch_x));
		this->m_Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		this->m_Right = glm::normalize(glm::cross(this->m_Front, this->m_WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->m_Up = glm::normalize(glm::cross(this->m_Right, this->m_Front));

		// �������� ������������ ���� ������� ������.
		m_Direction = this->m_Position + this->m_Front;
	}


}


	


